import time
import gpiod
from datetime import datetime
from gpiod.line import Direction, Value

# Custom logic level constants for the relay
PUMP_ON = Value.INACTIVE   # LOW = ON (activates relay)
PUMP_OFF = Value.ACTIVE    # HIGH = OFF (deactivates relay)


class PumpController:
    def __init__(self, chip_path="/dev/gpiochip0"):
        print("### Initializing")
        self.chip_path = chip_path

        self.line_offsets = {
            "pump0": 2,
            "pump1": 3,
        }

        self.request = gpiod.request_lines(
            self.chip_path,
            consumer="pump-controller",
            config={
                self.line_offsets["pump0"]: gpiod.LineSettings(
                    direction=Direction.OUTPUT,
                    output_value=PUMP_OFF
                ),
                self.line_offsets["pump1"]: gpiod.LineSettings(
                    direction=Direction.OUTPUT,
                    output_value=PUMP_OFF
                )
            },
        )

    def set_pump(self, pump_name, state):
        if pump_name not in self.line_offsets:
            raise ValueError(f"Unknown pump: {pump_name}")
        self.request.set_value(self.line_offsets[pump_name], state)

    def shutdown(self):
        # Set all pumps to OFF (HIGH) on shutdown
        for pump in self.line_offsets:
            self.set_pump(pump, PUMP_OFF)
        self.request.release()

    def pump_water(self, water_duration, pump_name):
        # Implement the logic for pumping water
        # The water_duration parameter can influence how much water is pumped
        if pump_name in self.line_offsets:
            print(datetime.now().strftime("%H:%M:%S") + ": " + str(pump_name) + " 0 activated for " + str(water_duration) + " seconds")
            self.set_pump(pump_name, PUMP_ON)
            time.sleep(water_duration)
            self.set_pump(pump_name, PUMP_OFF)
        else:
            print(datetime.now().strftime("%H:%M:%S") + ": Request for " + str(pump_name) + " received but no such pump available!")

# if __name__ == "__main__":
#     #controller = PumpController()

#     try:
#             print("Pump 1 ON")
#             controller.set_pump("pump0", PUMP_ON)
#             print("Pump 2 ON")
#             controller.set_pump("pump1", PUMP_ON)
#             print("Pump 1 OFF")
#             time.sleep(self.duration)
#             controller.set_pump("pump0", PUMP_OFF)
#             print("Pump 2 OFF")
#             controller.set_pump("pump1", PUMP_OFF)
#             controller.shutdown()

#     except KeyboardInterrupt:
#         print("Shutting down pumps safely...")
#         controller.shutdown()

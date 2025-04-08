import time
import gpiod
from datetime import datetime
from gpiod.line import Direction, Value
import logging

# Custom logic level constants for the relay
PUMP_ON = Value.INACTIVE   # LOW = ON (activates relay)
PUMP_OFF = Value.ACTIVE    # HIGH = OFF (deactivates relay)

# Configure logging
logging.basicConfig(
    filename="pump-logs.log",
    level=logging.DEBUG,  # Set the log level to DEBUG to capture all levels of logs
    format='%(asctime)s - %(levelname)s - %(message)s',  # Log format
)

class PumpController:
    def __init__(self, chip_path="/dev/gpiochip0"):
        logging.info("## Initializing PumpController")
        self.chip_path = chip_path

        self.line_offsets = {
            "pump0": 2,
            "pump1": 3,
        }

        logging.info("## Trigger request for GPIO lines")
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
        logging.info("## Initialization done, waiting for requests...")

    def set_pump(self, pump_name, state):
        if pump_name not in self.line_offsets:
            logging.warning("## pump " + pump_name + " not found!")
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
            logging.info("## " + str(pump_name) + " 0 activated for " + str(water_duration) + " seconds")
            self.set_pump(pump_name, PUMP_ON)
            time.sleep(water_duration)
            self.set_pump(pump_name, PUMP_OFF)
        else:
            logging.info("## Request for " + str(pump_name) + " received but no such pump available!")


# When standalone fired, to test run!
if __name__ == "__main__":
    

    controller = PumpController()

    try:
        logging.info("Pump 1 ON")
        controller.set_pump("pump0", PUMP_ON)
        logging.info("Pump 2 ON")
        controller.set_pump("pump1", PUMP_ON)
        logging.info("Pump 1 OFF")
        time.sleep(2)
        controller.set_pump("pump0", PUMP_OFF)
        logging.info("Pump 2 OFF")
        controller.set_pump("pump1", PUMP_OFF)
        logging.info("Shutting down...")
        controller.shutdown()

    except KeyboardInterrupt:
        logging.warning("Shutting down pumps safely after keyboard interrupt...")
        controller.shutdown()

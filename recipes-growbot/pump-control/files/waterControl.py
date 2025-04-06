import gpiod
import time
from gpiod.line_settings import Direction, Value


class GPIOWaterController:
    def __init__(self):
        self.chip_path = "/dev/gpiochip0"
        self.pin0 = 2
        self.pin1 = 3
        self.value = Value.INACTIVE  # Initial state
        self.value_str = {
            Value.ACTIVE: "Active",
            Value.INACTIVE: "Inactive"
        }

        # Set up the GPIO line
        self.request0 = gpiod.request_lines(
            self.chip_path,
            consumer="pump0-controller",
            config={
                self.pin0: gpiod.LineSettings(
                    direction=Direction.OUTPUT,
                    output_value=self.value,
                )
            }
        )
        
        self.request1 = gpiod.request_lines(
            self.chip_path,
            consumer="pump1-controller",
            config={
                self.pin1: gpiod.LineSettings(
                    direction=Direction.OUTPUT,
                    output_value=self.value,
                )
            }
        )

    def water(self):
        """Continuously toggle the GPIO pin every second."""
        try:
            self.request0.set_value(self.pin0, Value.ACTIVE)
            self.request1.set_value(self.pin1, Value.ACTIVE)
            time.sleep(5)
            self.request0.set_value(self.pin0, Value.INACTIVE)
            self.request1.set_value(self.pin1, Value.INACTIVE)
        except KeyboardInterrupt:
            print(f"Interrupted. Turning off pump on GPIO{self.pin}...")
            self.cleanup()
        except OSError as ex:
            print(f"OS Error: {ex}\nCheck your GPIO configuration.")
            self.cleanup()

    def cleanup(self):
        """Deactivate the pin and release it."""
        self.request0.set_value(self.pin0, Value.INACTIVE)
        self.request1.set_value(self.pin1, Value.INACTIVE)
        self.request0.release()
        self.request1.release()


if __name__ == "__main__":
    # Create two pumps
    pumps = GPIOWaterController()

    # Run pumps one after the other (you can parallelize this if needed)
    try:
        pumps.water()
        pumps.cleanup()

    except SystemError:
        pumps.cleanup()

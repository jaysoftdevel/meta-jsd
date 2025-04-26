import time
import os
import gpiod
from gpiod.line import Direction, Value

class DHT22:
    def __init__(self, pin):
        self.pin = pin
        self.chip = "/dev/gpiochip0"
        #self.line = self.chip.get_line(self.pin)
        self.line_offset = 26
        # Request the line once, but we'll request it for input and output as needed
        self.request = gpiod.request_lines(self.chip, consumer="dht22", config={self.line_offset : gpiod.LineSettings(direction=Direction.INPUT)})

    def _wait_for_level(self, expected_level, timeout_us):
        start = time.perf_counter()
        timeout_s = timeout_us / 1000000
        while (time.perf_counter() - start) < timeout_s:
            val = self.request.get_value(self.line_offset)
            if val == expected_level:
                return True
        return False

    def _send_start_signal(self):
        # Set the pin as output
        self.request.release()

        # Re-request as input for reading
        self.request = gpiod.request_lines(self.chip, consumer="dht22", config={self.line_offset : gpiod.LineSettings(direction=Direction.OUTPUT)})
        self.request.set_value(self.line_offset, Value.INACTIVE)  # Set LOW
        time.sleep(0.02)  # 20ms

        self.request.set_value(self.line_offset, Value.ACTIVE)  # Set HIGH
        time.sleep(0.00002)  # 20us
        self.request.set_value(self.line_offset, Value.INACTIVE)  # Set LOW
        
        # Set the pin as input again
        self.request.release()
        # Re-request as input for reading
        self.request = gpiod.request_lines(self.chip, consumer="dht22", config={self.line_offset : gpiod.LineSettings(direction=Direction.INPUT)})

    def _read_bit(self):
        if not self._wait_for_level(Value.INACTIVE, 100):
            return None
        if not self._wait_for_level(Value.ACTIVE, 100):
            return None
        start = time.perf_counter()
        while self.request.get_value(self.line_offset) == Value.ACTIVE:
            if (time.perf_counter() - start) > 0.0001:  # 100 us
                break
        pulse_length = (time.perf_counter() - start)
        return 1 if pulse_length > 0.00006 else 0

    def _read_data(self):
        bits = []
        for _ in range(40):
            bit = self._read_bit()
            if bit is None:
                raise RuntimeError("Timeout reading bit")
            bits.append(bit)
        return bits

    def _bits_to_bytes(self, bits):
        bytes_list = []
        for i in range(0, len(bits), 8):
            byte = 0
            for j in range(8):
                byte = (byte << 1) | bits[i + j]
            bytes_list.append(byte)
        return bytes_list

    def read(self):
        for attempt in range(3):  # try up to 3 times
            self._send_start_signal()
            try:
                bits = self._read_data()
                data = self._bits_to_bytes(bits)

                humidity = (data[0] << 8) | data[1]
                temperature = (data[2] << 8) | data[3]
                checksum = data[4]

                if ((sum(data[:4]) & 0xFF) != checksum):
                    raise RuntimeError("Checksum mismatch!")

                humidity /= 10.0
                if temperature & 0x8000:
                    temperature = -(temperature & 0x7FFF)
                temperature /= 10.0

                return temperature, humidity

            except Exception as e:
                #print(f"Read attempt {attempt+1} failed: {e}")
                time.sleep(0.5)  # short pause before retry
        raise RuntimeError("Failed to read from DHT22 after retries")

# Example usage
if __name__ == "__main__":
    sensor = DHT22(pin=26)  # BCM GPIO 26
    #try:
    temp, hum = sensor.read()
    print(f"Temperature: {temp:.1f} °C, Humidity: {hum:.1f} %")
    #except Exception as e:
    #    print(f"Failed to read sensor: {e}")

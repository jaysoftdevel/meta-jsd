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
        if(self.request is not None):
            self.request.release()

        # Now re-request as OUTPUT
        self.request = gpiod.request_lines(self.chip, consumer="dht22", config={self.line_offset : gpiod.LineSettings(direction=Direction.OUTPUT)})
        self.request.set_value(self.line_offset, Value.INACTIVE)  # LOW for start signal
        time.sleep(0.02)  # 20 ms

        self.request.set_value(self.line_offset, Value.ACTIVE)  # HIGH for 20-40 us
        time.sleep(0.00003)  # 30 us

        # Release and re-request as INPUT immediately
        self.request.release()
        self.request = gpiod.request_lines(self.chip, consumer="dht22", config={self.line_offset : gpiod.LineSettings(direction=Direction.INPUT)})

    def _read_bit(self):
        if not self._wait_for_level(Value.INACTIVE, 100):
            return None
        if not self._wait_for_level(Value.ACTIVE, 100):
            return None
        start = time.perf_counter()
        while self.request.get_value(self.line_offset) == Value.ACTIVE:
            if (time.perf_counter() - start) > 0.0002:  # 100 us
                break
        pulse_length = (time.perf_counter() - start)
        return 1 if pulse_length > 0.00004 else 0

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
        global temperature, humidity
        for attempt in range(3):  # try up to 3 times
            self._send_start_signal()
            try:
                bits = self._read_data()
                data = self._bits_to_bytes(bits)
                self.request.release()
                self.request = None


                humidity = (data[0] << 8) | data[1]
                temperature = (data[2] << 8) | data[3]
                checksum = data[4]

                if ((sum(data[:4]) & 0xFF) != checksum):
                    raise RuntimeError("Checksum mismatch!")

                humidity /= 10.0
                if temperature & 0x8000:
                    temperature = -(temperature & 0x7FFF)
                temperature /= 10.0
                
                if(temperature < 38.0 and temperature > 0.0):
                    return f"Temperature: {temperature:.1f} °C, Humidity: {humidity:.1f} %"
                elif(temperature >= 38.0 and temperature <= 80.0):
                    return f"Temperature: {temperature/2:.1f} °C, Humidity: {humidity/2:.1f} %"
                return f"Temperature: ERROR, Humidity: ERROR"
            except Exception as e:
                print(f"Read attempt {attempt+1} failed: {e}")
                time.sleep(0.5)  # short pause before retry
        
    def read_raw(self):
        global temperature, humidity 
        self.read()
        if(temperature != None):
            if(temperature < 38.0 and temperature > 0.0):
                return f"{(temperature)},{humidity}"
            elif(temperature >= 38.0 and temperature <= 80.0):
                return f"{temperature / 2},{humidity / 2}"
        # this means error!
        return f"0.0,0.0"



# Example usage
if __name__ == "__main__":
    humidity = None
    temperature = None
    sensor = DHT22(pin=26)  # BCM GPIO 26
    #try:
    print("read: " + str(sensor.read()))
    time.sleep(1)
    print("read_raw: " + str(sensor.read_raw()))
    #except Exception as e:

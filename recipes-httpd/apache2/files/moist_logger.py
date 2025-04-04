import serial
import datetime
import time

# Define the serial port and baud rate
SERIAL_PORT = "/dev/ttyACM0"  # Change to match your device
BAUD_RATE = 115200
DATA_BITS = serial.EIGHTBITS
PARITY = serial.PARITY_NONE  # 'N' (None)
STOP_BITS = serial.STOPBITS_ONE  # 1 stop bit
TIMEOUT = 1
LOGFILE = "moist_log.csv"

class moist_logger:
    def getMoist(self):
        try:
            # Open the serial port
            with serial.Serial(SERIAL_PORT, BAUD_RATE, bytesize=DATA_BITS, parity=PARITY, stopbits=STOP_BITS, timeout=TIMEOUT, rtscts=False, xonxoff=False) as ser:
                # Trigger first sensor
                ser.write(b'2') # Request both ADC values
                ser.flush()
                time.sleep(0.1)
                moist0 = ser.readline().decode('utf-8', errors='ignore').strip()
                date=datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                return f"{date},{moist0}\n"

        except serial.SerialException as e:
            print(f"Error: {e}")

        except serial.Timeout:
            print("Timeout!")

###### start ######
print("Starting soil moist monitor, logging into ")
m = moist_logger()

# empty log file
open(LOGFILE, "w").close()
while True:
    try:
        with open(LOGFILE, "a") as file:
            file.write(m.getMoist())
            file.flush()
        time.sleep(10)
    except KeyboardInterrupt:
        print("\nSerial reading stopped.")
        exit()

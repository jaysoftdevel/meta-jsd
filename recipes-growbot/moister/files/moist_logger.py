import serial
import datetime
import time
import logging

# Define the serial port and baud rate
SERIAL_PORT = "/dev/ttyAMA1"  # Change to match your device
BAUD_RATE = 115200
#DATA_BITS = serial.EIGHTBITS
#PARITY = serial.PARITY_NONE  # 'N' (None)
#STOP_BITS = serial.STOPBITS_ONE  # 1 stop bit
TIMEOUT = 10
LOGFILE = "/var/www/html/moist_log.csv"

ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=TIMEOUT)

class moist_logger:
    def getMoist(self):
        print("## getting moist..")
        try:
            ser.write("2".encode()) # Request both ADC values
            time.sleep(0.5)
            moist0 = ser.readline().decode('utf-8', errors='ignore').strip()
            date=datetime.datetime.now().strftime('%H:%M:%S')

            return f"{date},{moist0}\n"

        except serial.SerialException as e:
            logging.info(f"Error: {e.text()}")

        except serial.Timeout:
            logging.info("Timeout!")

    def startAtomzier(self):
        print("## starting atomizer")
        try:
            ser.write("3".encode())
            time.sleep(0.5)
            ser.flush()
            ser.close()
        except Exception as e:
            print(f"## ERROR during control: {e}")
#     return jsonify({"error": str(e)}), 500

    def stopAtomzier(self):
        print("## stop atomizer")
        ser.write("4".encode())
        time.sleep(0.5)
        ser.flush()
        ser.close()

###### start ######
#open("/var/www/html/growbot-logs.log", "a+").write("Starting soil moist monitor, logging into " + LOGFILE)
# m = moist_logger()

# while True:
#     try:
#         with open(LOGFILE, "a") as file:
#             file.write(m.getMoist())
#             file.flush()
#             #file.close() # free for streamer control
#         # once every minute (- drift correction, due to measurement)
#         time.sleep(59)
#     except KeyboardInterrupt:
#         logging.info("\nSerial reading stopped.")
#         exit()

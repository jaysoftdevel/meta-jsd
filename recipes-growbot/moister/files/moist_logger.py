import serial
import datetime
import time
import logging
import threading
import temperatureMeasure

# Define the serial port and baud rate
SERIAL_PORT = "/dev/ttyAMA1"  # Change to match your device
BAUD_RATE = 115200
#DATA_BITS = serial.EIGHTBITS
#PARITY = serial.PARITY_NONE  # 'N' (None)
#STOP_BITS = serial.STOPBITS_ONE  # 1 stop bit
TIMEOUT = 10
LOGFILE = "/var/www/html/moist_log.csv"

class moist_logger:
    def getMoist(self):
        print("## getting moist..")
        try:
            ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=TIMEOUT)
            ser.write("2".encode()) # Request both ADC values
            time.sleep(0.5)
            moist0 = ser.readline().decode('utf-8', errors='ignore').strip()
            date=datetime.datetime.now().strftime('%H:%M:%S')

            return f"{date},{moist0}"

        except serial.SerialException as e:
            logging.info(f"Error: {e.text()}")

        except serial.Timeout:
            logging.info("Timeout!")

    def startAtomzier(self):
        try:
            ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=TIMEOUT)
            ser.write("3".encode())
            time.sleep(0.5)
            ser.flush()
            ser.close()
        except Exception as e:
            print(f"## ERROR during control: {e}")
#     return jsonify({"error": str(e)}), 500

    def stopAtomzier(self):
        try:
            ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=TIMEOUT)
            ser.write("4".encode())
            time.sleep(0.5)
            ser.flush()
            ser.close()
        except Exception as e:
            print(f"## ERROR during control: {e}")

    def _run(self):
        while True:
            try:
                with open(LOGFILE, "a") as file:
                    # moist = self.getMoist()
                    # temp = 
                    file.write(f"{self.getMoist()},{temperatureMeasure.DHT22(26).read_raw()}\n")
                    file.flush()
                time.sleep(59)  # Wait 59 seconds
            except Exception as e:
                print(f"## ERROR during processing of file: {e}")

    def __init__(self):
        print("## init moister")
        self.thread = threading.Thread(target=self._run, daemon=True)
        self.thread.start()

    # def __init__(self):
    #     print("## init moister")
    #     while True:
    #         try:
    #             print("## open file")
    #             with open(LOGFILE, "a") as file:
    #                 file.write(self.getMoist())
    #                 file.flush()
    #                 print("## done writing")
    #                 file.close() # free for streamer control
    #                 print("## closed!!!")
    #             # once every minute (- drift correction, due to measurement)
    #             time.sleep(59)
    #         except KeyboardInterrupt:
    #             logging.info("\nSerial reading stopped.")
    #             exit()

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

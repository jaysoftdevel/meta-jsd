import serial
import time

ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=1)
print("UART echo test. Type something:")

while True:
    text = input("> ")
    ser.write(text.encode())

    # Wait for a response with a small delay to give the Arduino time to respond
    time.sleep(0.1)

    # Read echo back
    response = ser.readline().decode().strip()  # Using readline() to read until newline
    if response:
        print("Echo:", response)
    else:
        print("No response received.")
        
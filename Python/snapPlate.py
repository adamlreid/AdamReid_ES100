# ES100
# Adam Reid
# Python script to snap images of passing traffic for processing

# Designed for use with Arduino "deviceFinal" code

import cv2
import csv
import serial
import time
import os
from datetime import datetime

serial = serial.Serial('COM4', 9600)

# Open the camera
# Laptop:
cap = cv2.VideoCapture(0)
# Raspberry Pi 5

# Return if camera not found
if not cap.isOpened():
    print("Camera not found")
    exit()

# Define directory for vehicle images
auto_images = "auto_images"
os.makedirs(auto_images, exist_ok=True)

# Define csv file to collect data
deviceFinal = 'deviceFinal.csv'

if os.path.exists(deviceFinal):
    mode = 'a'
else:
    mode = 'w'

# Image capture instructions from Elegoo
initial = serial.readline().decode().strip()
print(initial)
if initial == '***':
    traffic_space = int(serial.readline().decode().strip()) / 1000 # convert from ms to seconds
    image_count = int(serial.readline().decode().strip())
    image_delay = float(serial.readline().decode().strip())

else:
    print("Elegoo not found")

initial_delay = traffic_space - (image_count * image_delay)

while True:
    # Read from the serial port
    scan = serial.readline().decode().strip()

    if scan == "autoDetect":
        print("Initializing...")
        time.sleep(initial_delay)

        for i in range(image_count):
            time.sleep(image_delay)
            retain, frame = cap.read()

            if retain:
                timestamp = int(time.time() * 1000) # Time in ms
                datestamp = datetime.now().strftime("%Y%m%d_%H%M%S_%f")[:-3] # no microseconds
                fileName = os.path.join(auto_images, f"sp_{datestamp}_{timestamp}.png")
                cv2.imwrite(fileName, frame)
                print(f"Image {i+1}/{image_count} taken")
            else:
                print("Image was not taken")

    # if scan == 'Summary:':
    #
    #     PMdata =
    #     with open(deviceFinal, mode, newline='') as file:
    #         writer = csv.writer(file)
    #
    #         for row in PMdata:
    #             writer.writerow(row)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

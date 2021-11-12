#!/usr/bin/env python
import time
import serial

comm_port = '/dev/ttyAMA0' # Change port_name to match your comm port name
baud_rate = 115200         # Other common rates: 9600, 57600
counter = 0

ser = serial.Serial(
    port = comm_port,
    baudrate = baud_rate,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS,
    timeout = 1
)


# Run this script on device sending serial data
while True:
        msg = "Write counter: %d \n"%(counter)
        print(msg)
        ser.write(msg.encode())
        time.sleep(0.5)
        counter += 1
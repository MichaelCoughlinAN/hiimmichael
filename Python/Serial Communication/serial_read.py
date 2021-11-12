#!/usr/bin/env python
import time
import serial

comm_port = 'COM4' # Change port_name to match your comm port name
baud_rate = 115200 # Other common rates: 9600, 57600

ser = serial.Serial(
    port = comm_port,
    baudrate = baud_rate,
    parity = serial.PARITY_NONE,
    stopbits = serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS,
    timeout = 1
)


# Run this script on device receiving serial data 
while True:
    print(ser.readline())
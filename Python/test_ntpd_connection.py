#!/usr/bin/env python

# Michael Coughlin
# hiimmichael.com
# 2019

import binascii
import datetime
import inspect
import logging
import os
import serial
import socket
import struct
import sys
import thread
import threading
import time


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    result = sock.connect_ex(('127.0.0.1', 123))
    if result == 0:
        print "Port is open"
    else:
        print "Port is not open"

if __name__ == "__main__":
    main()

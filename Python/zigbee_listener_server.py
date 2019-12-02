# Michael Coughlin
# hiimmichael.com
# 2019

import binascii
import idigidata
import logging
import os
import select
import socket
import sys
import threading
import time
import xbee


# Listen for frame from XBee radio
def listen_for_xbee_frame():
    global BUFFER_SIZE, xbee_socket
    msg = threading.currentThread().getName(), 'Running'
    print msg
    
    # Continuously listen for data on the XBee Socket
    while True:
        rs, ws, es = select.select([xbee_socket], [], [], 2)
        for r in rs:
            payload, source = r.recvfrom(BUFFER_SIZE)
            print 'rs'
            print payload

        for w in ws:
            payload, source = w.recvfrom(BUFFER_SIZE)
            print 'ws'
            print payload

        for e in es:
            payload, source = e.recvfrom(BUFFER_SIZE)
            print 'es'
            print payload

# Global Variables
BUFFER_SIZE = 1024  # Specifies the buffer size to read from
SENDING_TCP_PORT = 5000  # TCP Port used for AT Commands
tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Initialize the Proprietary Transport XBee Radio Socket
xbee_socket = socket.socket(socket.AF_ZIGBEE, socket.SOCK_DGRAM, socket.XBS_PROT_TRANSPORT)
xbee_socket.bind(("", 0xe8, 0, 0))


# Main function
def main():
    listen_for_xbee_frame()

if __name__ == "__main__":
    main()

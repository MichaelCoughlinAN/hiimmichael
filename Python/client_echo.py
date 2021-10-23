#!/usr/bin/env python

# Michael Coughlin
# hiimmichael.com
# 2019

import socket


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 5001))

while 1:
    data, client = sock.recvfrom(256)
    sock.sendto("hello", client)
    print "Connected to " + client[0]

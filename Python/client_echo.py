#!/usr/bin/env python

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 5001))
#00bfff
while 1:
    data, client = sock.recvfrom(256)
    sock.sendto("hello", client)
    print "Connected to " + client[0]
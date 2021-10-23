#!/usr/bin/env python

# Michael Coughlin
# hiimmichael.com
# 2019

import socket
import struct

MCAST_GRP = '230.0.0.0'
MCAST_PORT = 4446

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', MCAST_PORT))  # use MCAST_GRP instead of '' to listen only

mreq = struct.pack("4sl", socket.inet_aton(MCAST_GRP), socket.INADDR_ANY)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

print 'running'

while True:
  print 'hello' +  sock.recv(10240)

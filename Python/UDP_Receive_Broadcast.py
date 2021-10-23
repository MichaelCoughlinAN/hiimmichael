# Michael Coughlin
# hiimmichael.com
# 2019

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('', 1080))

while True:
    print(s.recv(1024))

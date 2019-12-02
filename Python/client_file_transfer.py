#!/usr/bin/env python

# Michael Coughlin
# hiimmichael.com
# 2019

import socket


TCP_IP = '192.168.1.1' #IPv4 address
TCP_PORT = 9001
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))

with open('received_file', 'wb') as f:
    print 'file opened'
    
    while True:
        #print('receiving data...')
        data = s.recv(BUFFER_SIZE)
        print('data=%s', (data))
        if not data:
            f.close()
            print 'file close()'
            break
        # write data to a file
        f.write(data)

print('Successfully get the file')
s.close()
print('connection closed')

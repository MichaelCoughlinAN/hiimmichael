#!usr/bin/python

# Michael Coughlin
# hiimmichael.com
# 2019

import socket


def main():
    TCP_IP = ''
    TCP_PORT = 5009
    BUFFER_SIZE = 20  # Normally 1024, but we want a fast response

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(1)

    conn, addr = s.accept()
    print 'Connection address:', addr
    while 1:
        data = conn.recv(BUFFER_SIZE)
        if not data: break
        print "received data:", data
        conn.send(data)  # echo
    conn.close()


if __name__ == "__main__":
    main()

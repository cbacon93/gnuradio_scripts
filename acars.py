#!/usr/bin/python

import socket
import sys

UDP_IP = '127.0.0.1'
UDP_PORT = 1737

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((UDP_IP, UDP_PORT))

while 1:
    data = s.recv(1024)
    #print data,
    sys.stdout.write(data);

conn.close()

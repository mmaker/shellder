#!/usr/bin/python -u
from time import sleep
from os import getpid
from sys import argv

ping = argv[1] if len(argv) > 1 else 'ping %d' % getpid()
delay = int(argv[2]) if len(argv) > 2 else 1

while True:
    print ping
    sleep(delay)

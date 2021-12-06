
import socket
import sys

def portScanner(target, port):
    if s.connect_ex((target,port)):
        print('port '+str(port)+' is closed')
    else:
        print('port '+str(port)+' is open')

def portsScanner(target, startport, endport):
    for port in range(startport, endport):
        portScanner(target,port)
    print('scan is comlete\n')

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.settimeout(5)

target = str(sys.argv[1])
startport = int(sys.argv[2])
endport = int(sys.argv[3])

portsScanner(target, startport, endport)
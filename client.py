from codecs import encode
import socket
import _thread
import sys
import select
import signal

FORMAT = "utf-8"
IP = '127.0.0.1'
PORT = 5000
USER_NAME =input("enter your name: ")

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
c.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
"""
def receiveSignal():
    c.send("") 
    exit()

signal.signal(signal.SIGINT, receiveSignal)

"""

#print(f"[*] Connecting to {IP}:{PORT}...")
c.connect((IP,PORT))
#print("[+] Connected.")

while True:
 
    sockets_list = [sys.stdin, c]

    read_sockets,write_socket, error_socket = select.select(sockets_list,[],[])
 
    for socks in read_sockets:
        if socks == c:
            message = socks.recv(2048).decode()
            print (message)
        else:
            message = sys.stdin.readline()
            x = f"{USER_NAME}: {str(message)}"
            c.send(x.encode(FORMAT))
            sys.stdout.write(x)
            sys.stdout.flush()
c.close()
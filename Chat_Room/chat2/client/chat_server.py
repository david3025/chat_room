import socket
import threading
import os


IP_address = "127.0.0.1"
Port = 8001
SIZE = 1024
FORMAT = "utf-8"
SERVER_DATA_PATH ="server"

def send_msg(conn, msg):
    conn.send(msg.encode(FORMAT))

def list(conn):

    files = os.listdir(SERVER_DATA_PATH)
    send_data = ""
    if len(files) == 0:
        send_data += "The server directory is empty"
    else:
        send_data += "\n".join(f for f in files)
    conn.send(send_data.encode(FORMAT))
    


def clientthread(conn,addr):

    conn.send("Welcome to this chatroom!".encode(FORMAT))

    
    while True:

        data = conn.recv(SIZE).decode(FORMAT)
        data = data.split("
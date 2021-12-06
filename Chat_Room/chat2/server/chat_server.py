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
        data = data.split("**")

        command = data[0]
       

        if command == "LIST":
            
            list(conn)

        elif command == "DELETE":
            pass

        elif command == "UPLOAD":
            pass
       
        elif command == "DOWNLOAD":
            pass

        elif command == "LOGOUT":
            pass

        elif command == "PRINT":
            pass

        
    



def main():

    list_of_clients = []

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # socket()
    print ("Socket successfully created")
    server.bind((IP_address, Port))         # bind()
    server.listen(100)                      # listen()
    print("server listen..")

    while True:
        conn, addr = server.accept()       # accept()
        list_of_clients.append(conn)

        print(f"{addr} connected")

        x = threading.Thread(target=clientthread, args=(conn,addr))
        x.start()

if __name__ == "__main__":
    main()


""""
if command == "LIST":
            send_command(conn, command)

        elif command == "DELETE":
            pass

        elif command == "UPLOAD":
            pass
       
        elif command == "DOWNLOAD":
            pass

        elif command == "LOGOUT":
            send_command(conn, command)"""
#-------------------------version 2--------------------------------

import socket
import threading
import os
#-----------------------------------------------------------------

IP_address = "127.0.0.1"
Port = 8001
SIZE = 1024
FORMAT = "utf-8"
SERVER_DATA_PATH ="server"
SPLIT = '**'
#-----------------------------------------------------------------

def send_msg(conn, msg):
    conn.send(msg.encode(FORMAT))

def remove(conn, data):
    print("in remove")
    files = os.listdir(SERVER_DATA_PATH)
    send_data = ""
    filename = data[1]

    if len(files) == 0:
        send_data += "The server directory is empty"
    else:
        if filename in files:
            os.system(f"rm {SERVER_DATA_PATH}/{filename}")
            send_data += "File deleted successfully."
        else:
            send_data += "File not found."
    
    send_msg(conn,send_data)

def list(conn):

    files = os.listdir(SERVER_DATA_PATH)
    send_data = ""
    if len(files) == 0:
        send_data += "The server directory is empty"
    else:
        send_data += "\n".join(files)
    send_msg(conn,send_data)

def read_and_send(conn,path,command):

    send_data =f"{command}{SPLIT}"
    if os.path.isfile(path):

        with open(f"{path}", "r") as f:
                    text = f.read()

        filename = path.split("/")[-1]
        send_data += f"{filename}{SPLIT}{text}"
        
    else:
        send_data += "File not found."

    send_msg(conn, send_data)

def save_file(conn, data, PATH):

    name, text = data[1], data[2]
    filepath = os.path.join(PATH, name)
    with open(filepath, "w") as f:
        f.write(text)
    send_msg(conn,"File uploaded successfully")
    

def clientthread(conn,addr):

    conn.send("Welcome to this chatroom!".encode(FORMAT))

    
    while True:

        data = conn.recv(SIZE).decode(FORMAT)
        data = data.split("**")

        command = data[0]
       

        if command == "LIST":
            list(conn)

        elif command == "DELETE":
            print(data)
            remove(conn, data)

        elif command == "UPLOAD":
            save_file(conn, data, SERVER_DATA_PATH)

        elif command == "DOWNLOAD":

            file_name = data[1]
            path = f"{SERVER_DATA_PATH}/{file_name}"
            read_and_send(conn,path,command)
            send_msg(conn,"File downloaded successfully")
            
        elif command == "LOGOUT":
            break

        elif command == "PRINT":
            pass

#-----------------------------------------------------------------
#         
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


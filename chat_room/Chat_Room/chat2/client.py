#-------------------------version 2--------------------------------

import socket
import os

#-----------------------------------------------------------------

list_of_CLI = ["LIST","DELETE","UPLOAD","DOWNLOAD","LOGOUT","PRINT"]
IP_address = "127.0.0.1"
Port = 8001
SIZE = 1024
FORMAT = "utf-8"
SPLIT = '**'
CLIENT_DATA_PATH ="client"

#-----------------------------------------------------------------

def send_msg(conn, msg):
    conn.send(msg.encode(FORMAT))

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
    

#----------------------------------------------  
#   
def user_cli(conn):
   
    while True:

        msg = conn.recv(SIZE).decode(FORMAT)
        print(msg)
        
        data = input("> ").split(" ")

        # Checks whether the command is correct
        while data[0] not in list_of_CLI:
            print("There is a mistake in command-try again")
            data = input("> ").split(" ")

        command = data[0]  

        if command == "LIST":
            send_msg(conn, command)

        elif command == "LOGOUT":
            send_msg(conn,command) 

        elif command == "DELETE":
            msg = f"{SPLIT}".join(data)
            send_msg(conn,msg) 

        elif command == "UPLOAD":
            path=data[1]
            read_and_send(conn, path, command)


        elif command == "DOWNLOAD":
            
            msg = f"{SPLIT}".join(data)
            send_msg(conn, msg)
##
            data = conn.recv(SIZE).decode(FORMAT)
            
            data = data.split(f"{SPLIT}")
            save_file(conn,data,CLIENT_DATA_PATH)


        elif command == "PRINT":
            pass
#-----------------------------------------------------------------     

def main():
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((IP_address, Port))
    user_cli(conn) 
    conn.close()

if __name__ == "__main__":
    main()
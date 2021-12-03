import socket
import os
list_of_CLI = ["LIST","DELETE","UPLOAD","DOWNLOAD","LOGOUT","PRINT"]
IP_address = "127.0.0.1"
Port = 8001
SIZE = 1024
FORMAT = "utf-8"
SPLIT = '**'
CLIENT_DATA_PATH ="client"

def send_command(conn, data):
    data=f'{SPLIT}'.join(data)
    conn.send(data.encode(FORMAT))


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
            conn.send(command.encode(FORMAT))
            #send_command(conn, data)
            print("sfvf")

        elif command == "LOGOUT":
            send_command(conn, command)
        
        elif command == "DELETE":
            send_command(conn, command)

        elif command == "UPLOAD":
            pass
       
        elif command == "DOWNLOAD":
            pass

        elif command == "PRINT":
            pass

        conn.send("SIZE".encode(FORMAT))
        msg = conn.recv(SIZE).decode(FORMAT)
        print(msg)

def main():
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((IP_address, Port))
    user_cli(conn) 
    conn.close()

if __name__ == "__main__":
    main()
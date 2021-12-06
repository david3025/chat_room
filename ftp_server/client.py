#david-levi

import socket
import os #path.isfile,

#----------------------------------------------------------

IP = "127.0.0.1"
PORT = 9090
ADDR = (IP, PORT)
FORMAT = "utf-8"
SIZE = 1024
CLIENT_DATA_PATH = "client"

#----------------------------------------------------------
#When I send messages between Server and Client 
#I divide a string of sections using a "Split" 
# with a partition of "@" 
#for exemple:            send_data = f"{cmd}@{filename}@{DATA}"
#And when receiving getting the sending 
# is making a split :    data = data.split("@")
# just the recipient makes the split
#----------------------------------------------------------
def print_manual():

    print(f"\n---------------------------------")
    print("LIST: List all the files\nUPLOAD <path>\nDOWNLOAD <path>\nDELETE <filename>\nLOGOUT: Disconnect")
    print("---------------------------------\n")


def send_data(client,path,cmd):

    if os.path.isfile(path):

        with open(f"{path}", "r") as f:
                    text = f.read()

        filename = path.split("/")[-1]
        send_data = f"{cmd}@{filename}@{text}"
        client.send(send_data.encode(FORMAT))
    else:
        
        send_data = "PRINT@File not found."
        client.send(send_data.encode(FORMAT))



def save_file(conn,data, PATH):

    data = data.split("@")
    name, text = data[1], data[2]
    filepath = os.path.join(PATH, name)

    with open(filepath, "w") as f:
        f.write(text)

    send_data = "PRINT@File downloaded successfully."
    conn.send(send_data.encode(FORMAT))

#--------------------------USER-CLI-------------------------------

def user_cli(client):

    list_of_CLI = ["LIST","DELETE","UPLOAD","DOWNLOAD","LOGOUT"]

    while True:

        msg = client.recv(SIZE).decode(FORMAT)

        print(f"\n{msg}") 

        print_manual()

        data = input("> ").split(" ")

        # Checks whether the command is correct
        while data[0] not in list_of_CLI:

            print("There is a mistake in command-try again")
            data = input("> ").split(" ")

        cmd = data[0]

        if cmd == "LIST":
            client.send(cmd.encode(FORMAT))

        elif cmd == "DELETE":
            client.send(f"{cmd}@{data[1]}".encode(FORMAT))

        elif cmd == "UPLOAD":
            path = data[1]
            send_data(client, path, cmd)
            
        elif cmd == "DOWNLOAD":

            filename = data[1]
            send_dat = f"{cmd}@{filename}"

            client.send(send_dat.encode(FORMAT))
            data = client.recv(SIZE).decode(FORMAT)
            save_file(client,data,CLIENT_DATA_PATH)
            
        elif cmd == "LOGOUT":
            client.send(cmd.encode(FORMAT))
            break

#----------------------------------------------------------

def main():

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)
    print("connected to the server.")

    user_cli(client)

    print("Disconnected from the server.")
    client.close()

#----------------------------------------------------------

if __name__ == "__main__":
    main()

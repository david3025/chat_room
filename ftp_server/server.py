#david-levi
#server
import socket #socket
import os #listdir, path, system
import threading#Thread
#----------------------------------------------------------

IP = "127.0.0.1"
PORT = 9090
ADDR = (IP, PORT)
SIZE = 1024
FORMAT = "utf-8"
SERVER_DATA_PATH = "server"

#----------------------------------------------------------
#When I send messages between Server and Client 
#I divide a string of sections using a "Split" 
# with a partition of "@" 
#for exemple:            send_data = f"{cmd}@{filename}@{DATA}"
#And when receiving getting the sending 
# is making a split :    data = data.split("@")
# just the recipient makes the split
#----------------------------------------------------------

def list(conn):

    files = os.listdir(SERVER_DATA_PATH)
    send_data = ""
    if len(files) == 0:
        send_data += "The server directory is empty"
    else:
        send_data += "\n".join(f for f in files)
    conn.send(send_data.encode(FORMAT))

def send_data(conn,filename,cmd):

    with open(f"{SERVER_DATA_PATH}/{filename}", "r") as f:
                text = f.read()
    send_data = f"{cmd}@{filename}@{text}"
    conn.send(send_data.encode(FORMAT))

def save_file(conn, data, PATH):

    name, text = data[1], data[2]
    filepath = os.path.join(PATH, name)
    with open(filepath, "w") as f:
        f.write(text)

    send_data = "File uploaded successfully."
    conn.send(send_data.encode(FORMAT))

def remove(conn, data):

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

    conn.send(send_data.encode(FORMAT))

#-------------------------SERVER-API------------------------------

def server_api(conn, addr):

    print(f"connected {addr}")

    conn.send("Welcome to the File Server.".encode(FORMAT))

    while True:

        data = conn.recv(SIZE).decode(FORMAT)
        data = data.split("@")
        cmd = data[0]

        if cmd == "LIST":
            list(conn)

        elif cmd == "DELETE":
            remove(conn, data) 

        elif cmd == "UPLOAD":
            save_file(conn, data,SERVER_DATA_PATH)

        elif cmd == "DOWNLOAD":
            filename = data[1]
            send_data(conn,filename,cmd)
            
        elif cmd == "PRINT":
            print(data[1])
            conn.send(f"{data[1]}".encode(FORMAT))

        elif cmd == "LOGOUT":
            break

    print("disconnected")
    conn.close()

#----------------------------------------------------------

def main():

    print("Server is starting")
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(ADDR)
    server.listen()
    print(f"Server is listening on {IP}:{PORT}.")

    while True:
		# Wait for connections
        conn, addr = server.accept()

        # Listen for messages on this connection
        listener = threading.Thread(target=server_api, args=(conn, addr))
        listener.start()
#----------------------------------------------------------

if __name__ == "__main__":
    main()

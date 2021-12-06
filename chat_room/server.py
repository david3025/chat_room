##Python codes to do server-side part of chat room.
import _thread
import socket

IP="127.0.0.1"
PORT=5000
CLIENTS=[]
FORMAT = "utf-8"



def connect_new_client(c):
     while True:
        msg = c.recv(2048)
        if len(msg) == 0:
            CLIENTS.remove(c)
            
        for client in CLIENTS:
            if client == c :
                continue
            client.send(msg) 
        



def main():
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)  
    s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    s.bind((IP,PORT))
    s.listen(5)
    print("listening...")    

    while True:
        c,ad=s.accept()
        print(f'Server Connected {ad}')
        CLIENTS.append(c)

        _thread.start_new_thread(connect_new_client,(c,))


if __name__ == "__main__":
    main()

from tkinter import *
import os
import socket
#-----------------------------------------------------------------

list_of_CLI = ["LIST","DELETE","UPLOAD","DOWNLOAD","LOGOUT","PRINT"]
IP_address = "127.0.0.1"
Port = 8001
SIZE = 1024
FORMAT = "utf-8"
SPLIT = '**'
CLIENT_DATA_PATH ="client"
#-----------------------------------------------------------------
conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
conn.connect((IP_address, Port))
#-----------------------------------------------------------------
window = Tk()

e_input_value = StringVar()
e_input=Entry(window,textvariable=e_input_value)
e_input.grid(row=3,column=3)

#----------------------------------------------------------
def send_msg(conn, msg):
    conn.send(msg.encode(FORMAT))

def read_and_send(conn,command = "UPLOAD"):
    path=e_input_value.get()
    send_data =f"{command}{SPLIT}"
    if os.path.isfile(path):

        with open(f"{path}", "r") as f:
                    text = f.read()

        filename = path.split("/")[-1]
        send_data += f"{filename}{SPLIT}{text}"
        
    else:
        send_data += "File not found."

    send_msg(conn, send_data)

#----------------------------------------------------------
def print_list():
    input=e_input_value.get()
    t_outpt.insert(END,input)




b_list=Button(window, text="list", command=print_list)
b_list.grid(row=1,column=1)

b_upload=Button(window, text="upload",command=read_and_send)
b_upload.grid(row=2,column=1)

b_download=Button(window, text="download")
b_download.grid(row=1,column=2)

b_delete=Button(window, text="delete")
b_delete.grid(row=2,column=2)

b_logout=Button(window, text="logout")
b_logout.grid(row=1,column=3)




t_outpt=Text(window,height=5,width=15)
t_outpt.grid(row=4,column=3)

window.mainloop()



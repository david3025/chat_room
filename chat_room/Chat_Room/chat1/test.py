# Python program to determine which
# button was pressed in tkinter

# Import the library tkinter
from tkinter import *

import socket

IP_address = "127.0.0.1"
Port = 8001
SIZE = 1024
FORMAT = "utf-8"
list_of_CLI = ["LIST","DELETE","UPLOAD","DOWNLOAD","LOGOUT","PRINT"]

conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
conn.connect((IP_address, Port))

# Create a GUI app
window = Tk()



# Creating and displaying of button b1
b_list = Button(window, text="LIST")

b_list.grid(padx=10, pady=10)

e_input_value = StringVar()
e_input=Entry(window,textvariable=e_input_value)
e_input.grid(row=3,column=3)

t_outpt=Text(window,height=5,width=15)
t_outpt.grid(row=4,column=3)



def send_msg(conn, msg):
    conn.send(msg.encode(FORMAT))

while True:

        msg = conn.recv(SIZE).decode(FORMAT)
        
        t_outpt.insert(END,msg)

	

        data = input("> ").split(" ")

        # Checks whether the command is correct
        while data[0] not in list_of_CLI:
            print("There is a mistake in command-try again")
            data = input("> ").split(" ")

        command = data[0]  

        if command == "LIST":
            send_msg(conn, command)



# Make the infinite loop for displaying the app
window.mainloop()


import socket
import threading
from tkinter import *
import tkinter as tk

PORT = 12345

def receive_data(entry_widget):
    print("receiving...")
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind(('192.168.5.1', PORT))
            s.listen(1)
            while True:
                conn, addr = s.accept()
                with conn:
                    print('Receiver Connected by', addr)
                    while True:
                        data = conn.recv(1024)
                        if not data: break
                        print("loopback data: " + str(data))
                        conn.send(bytes(str(data).replace('\'', "") + ' returned', 'utf-8'))
            s.close()
            s = None
    except Exception as e:
        print(f"An error occurred: {str(e)}")
        s.close()
        s = None



def send_data(entry_widget):
    data = entry_widget.get()
    if data:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(("192.168.5.10", PORT))
            s.send(data.replace('\'', "").encode('utf-8'))
            print("data sent")
            recv_data = s.recv(1024)
            text_widget.insert(END,"\n" + bytes(recv_data).hex())
        s.close()
        s=None

def create_window(title):
    window = tk.Tk()
    window.title(title)
    label = tk.Label(window, text="FL: ")
    label.pack()
    entry = tk.Entry(window)
    entry.insert(END,"ENTRY")
    entry.pack()
    send_button = tk.Button(window, text="Send", command= lambda: send_data(entry))
    send_button.pack()
    text_widget = tk.Text(window)
    text_widget.insert(END, "Receiving...")
    text_widget.pack()
    return window, entry, text_widget

if __name__ == "__main__":
    #client_socket = None

    # Create two separate windows for the client and server
    client_window, client_entry, text_widget = create_window("Client")
    #server_window, server_entry, text_widget = create_window("Server")

    recv_thread = threading.Thread(target=receive_data, args=(client_entry, )).start()
    
    client_window.mainloop()
    #server_window.mainloop()

#!/usr/bin/python3
import tkinter as tk
from tkinter import *
from tkinter import ttk
import threading
import socket
import json


class RootbotWidget(tk.Frame):
    PORT = 12345
    ADDR = '192.168.5.10'
    HOST = '192.168.5.1'
    # ADDR = 'localhost'
    # HOST = 'localhost'

    def __init__(self, master=None, **kw):
        super(RootbotWidget, self).__init__(master, **kw)

        # Set the DPI explicitly (change the value as needed)
        self.DisplayData = tk.Frame(self)
        self.DisplayData.configure(
            borderwidth=5,
            height=200,
            padx=5,
            pady=5,
            width=200)
        self.lblFL = tk.Label(self.DisplayData)
        self.lblFL.configure(text='FL')
        self.lblFL.grid(column=1, row=0)
        self.lblFC = tk.Label(self.DisplayData)
        self.lblFC.configure(text='FC')
        self.lblFC.grid(column=3, row=0)
        self.lblFR = tk.Label(self.DisplayData)
        self.lblFR.configure(text='FR')
        self.lblFR.grid(column=5, row=0)
        self.lblRL = tk.Label(self.DisplayData)
        self.lblRL.configure(text='RL')
        self.lblRL.grid(column=2, row=4)
        self.lblRR = tk.Label(self.DisplayData)
        self.lblRR.configure(text='RR')
        self.lblRR.grid(column=4, row=4)
        self.lblML = tk.Label(self.DisplayData)
        self.lblML.configure(text='ML')
        self.lblML.grid(column=2, row=2)
        self.lblMR = tk.Label(self.DisplayData)
        self.lblMR.configure(text='MR')
        self.lblMR.grid(column=4, row=2)
        self.lblPing = tk.Label(self.DisplayData)
        self.lblPing.configure(text='Ping')
        self.lblPing.grid(column=2, row=6)
        self.lblLoad = tk.Label(self.DisplayData)
        self.lblLoad.configure(text='Load')
        self.lblLoad.grid(column=4, row=6)
        self.entryFL = tk.Entry(self.DisplayData)
        self.entryFL.configure(width=5)
        self.entryFL.insert(END,"0")
        self.entryFL.grid(column=2, row=0)
        self.entryFC = tk.Entry(self.DisplayData)
        self.entryFC.configure(width=5)
        self.entryFC.insert(END,"0")
        self.entryFC.grid(column=4, row=0)
        self.entryFR = tk.Entry(self.DisplayData)
        self.entryFR.configure(width=5)
        self.entryFR.grid(column=6, row=0)
        self.entryFR.insert(END,"0")
        self.entryRL = tk.Entry(self.DisplayData)
        self.entryRL.configure(width=5)
        self.entryRL.grid(column=3, row=4)
        self.entryRL.insert(END,"0")
        self.entryRR = tk.Entry(self.DisplayData)
        self.entryRR.configure(width=5)
        self.entryRR.grid(column=5, row=4)
        self.entryRR.insert(END,"0")
        self.entryML = tk.Entry(self.DisplayData)
        self.entryML.configure(width=5)
        self.entryML.grid(column=3, row=2)
        self.entryML.insert(END,"0")
        self.entryMR = tk.Entry(self.DisplayData)
        self.entryMR.configure(width=5)
        self.entryMR.grid(column=5, row=2)
        self.entryMR.insert(END,"0")
        self.entryPing = tk.Entry(self.DisplayData)
        self.entryPing.configure(width=5)
        self.entryPing.grid(column=3, row=6)
        self.entryPing.insert(END,"0")
        self.entryLoad = tk.Entry(self.DisplayData)
        self.entryLoad.configure(width=5)
        self.entryLoad.grid(column=5, row=6)
        self.entryLoad.insert(END,"0")
        self.ckbCS_state = tk.BooleanVar()
        self.ckbCS = tk.Checkbutton(self.DisplayData, variable=self.ckbCS_state)
        self.ckbCS.configure(text=' CS', width=5)
        self.ckbCS.grid(column=1, row=6)
        self.btnSend = tk.Button(self.DisplayData, text="Send", command=lambda: self.send_data())
        self.btnSend.configure(padx=10, pady=10, text='Send')
        self.btnSend.grid(column=3, row=8)
        self.sclFL = tk.Scale(self.DisplayData, command=self.update_entry_FL)
        self.sclFL.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclFL.grid(column=2, row=1)
        self.sclFC = tk.Scale(self.DisplayData, command=self.update_entry_FC)
        self.sclFC.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclFC.grid(column=4, row=1)
        self.sclFR = tk.Scale(self.DisplayData, command=self.update_entry_FR)
        self.sclFR.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclFR.grid(column=6, row=1)
        self.sclML = tk.Scale(self.DisplayData, command=self.update_entry_ML)
        self.sclML.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclML.grid(column=3, row=3)
        self.sclMR = tk.Scale(self.DisplayData, command=self.update_entry_MR)
        self.sclMR.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclMR.grid(column=5, row=3)
        self.sclRL = tk.Scale(self.DisplayData, command=self.update_entry_RL)
        self.sclRL.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclRL.grid(column=3, row=5)
        self.sclRR = tk.Scale(self.DisplayData, command=self.update_entry_RR)
        self.sclRR.configure(orient="horizontal", tickinterval=127, to=255)
        self.sclRR.grid(column=5, row=5)
        # self.ckbFront = tk.Checkbutton(self.DisplayData)
        # self.ckbFront.configure(text='FronSensors live')
        # self.ckbFront.grid(column=0, row=0, sticky="w")
        # self.ckbRear = tk.Checkbutton(self.DisplayData)
        # self.ckbRear.configure(text='RearSensors live')
        # self.ckbRear.grid(column=0, row=4, sticky="w")
        # self.ckbConnection = tk.Checkbutton(self.DisplayData)
        # self.ckbConnection.configure(text='Connection live')
        # self.ckbConnection.grid(column=0, row=6, sticky="w")
        self.sclLoad = tk.Scale(self.DisplayData, command=self.update_entry_Load)
        self.sclLoad.configure(orient="horizontal")
        self.sclLoad.grid(column=5, row=7)
        self.sclPing = tk.Scale(self.DisplayData, command=self.update_entry_Ping)
        self.sclPing.configure(orient="horizontal")
        self.sclPing.grid(column=3, row=7)
        # self.ckbMotor = tk.Checkbutton(self.DisplayData)
        # self.ckbMotor.configure(text='Motor live')
        # self.ckbMotor.grid(column=0, row=2, sticky="w")
        self.DisplayData.grid(column=0, row=1)
        self.ResponseFrame = tk.Frame(self)
        self.ResponseFrame.configure(height=200, width=200)
        self.txtResponse = tk.Text(self.ResponseFrame)
        self.txtResponse.configure(height=20, width=80,state="disabled")
        self.txtResponse.pack(side="top")
        self.ResponseFrame.grid(column=0, row=2)
        self.LiveFrame = tk.Frame(self)
        self.LiveFrame.configure(height=200, width=200)
        self.ckbLive_state = tk.BooleanVar()
        self.ckbLive = tk.Checkbutton(self.LiveFrame, command=self.enable_live, variable=self.ckbLive_state)
        self.ckbLive.configure(text='Enable live mode')
        self.ckbLive.grid(column=0, row=0, sticky="w")
        self.sclInterval_value = tk.IntVar()
        self.sclInterval = tk.Scale(self.LiveFrame,variable=self.sclInterval_value)
        self.sclInterval.configure(
            from_=5,
            label='Interval (ms)',
            orient="horizontal",
            to=5000
            )
        self.sclInterval.set(1000)
        self.sclInterval.grid(column=2, row=0, sticky="e")
        self.lblSpacer = tk.Label(self.LiveFrame)
        self.lblSpacer.configure(width=25)
        self.lblSpacer.grid(column=1, row=0)
        self.LiveFrame.grid(column=0, row=0)
        self.EchoFrame = tk.Frame(self)
        self.EchoFrame.configure(height=200, width=200)
        self.EchoFrame.grid(column=0, row=3)
        self.lblEchoTitle = tk.Label(self.EchoFrame, text="RemoteStatus:       ", relief="sunken", compound="left",padx=10)
        self.lblEchoTitle.grid(row=0, column=0)
        self.lblEchoFL = tk.Label(self.EchoFrame)
        self.lblEchoFL.configure(text='FL')
        self.lblEchoFL.grid(column=1, row=0)
        self.lblEchoFC = tk.Label(self.EchoFrame)
        self.lblEchoFC.configure(text='FC')
        self.lblEchoFC.grid(column=3, row=0)
        self.lblEchoFR = tk.Label(self.EchoFrame)
        self.lblEchoFR.configure(text='FR')
        self.lblEchoFR.grid(column=5, row=0)
        self.lblEchoRL = tk.Label(self.EchoFrame)
        self.lblEchoRL.configure(text='RL')
        self.lblEchoRL.grid(column=2, row=4)
        self.lblEchoRR = tk.Label(self.EchoFrame)
        self.lblEchoRR.configure(text='RR')
        self.lblEchoRR.grid(column=4, row=4)
        self.lblEchoML = tk.Label(self.EchoFrame)
        self.lblEchoML.configure(text='ML')
        self.lblEchoML.grid(column=2, row=2)
        self.lilEchoMR = tk.Label(self.EchoFrame)
        self.lilEchoMR.configure(text='MR')
        self.lilEchoMR.grid(column=4, row=2)
        self.lblEchoPing = tk.Label(self.EchoFrame)
        self.lblEchoPing.configure(text='Ping')
        self.lblEchoPing.grid(column=2, row=6)
        self.lblEchoLoad = tk.Label(self.EchoFrame)
        self.lblEchoLoad.configure(text='Load')
        self.lblEchoLoad.grid(column=4, row=6)
        self.sclEchoFL = tk.Scale(self.EchoFrame)
        self.sclEchoFL.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoFL.grid(column=2, row=1)
        self.sclEchoFC = tk.Scale(self.EchoFrame)
        self.sclEchoFC.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoFC.grid(column=4, row=1)
        self.sclEchoFR = tk.Scale(self.EchoFrame)
        self.sclEchoFR.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoFR.grid(column=6, row=1)
        self.sclEchoML = tk.Scale(self.EchoFrame)
        self.sclEchoML.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoML.grid(column=3, row=3)
        self.sclEchoMR = tk.Scale(self.EchoFrame)
        self.sclEchoMR.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoMR.grid(column=5, row=3)
        self.sclEchoRL = tk.Scale(self.EchoFrame)
        self.sclEchoRL.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoRL.grid(column=3, row=5)
        self.sclEchoRR = tk.Scale(self.EchoFrame)
        self.sclEchoRR.configure(orient="horizontal", tickinterval=127, to=255, state="disabled")
        self.sclEchoRR.grid(column=5, row=5)
        self.pack(side="top")

    def enable_live(self):
        live_thread = None
        if(self.ckbLive_state.get()==True):
            self.btnSend.config(state="disabled")
            live_thread = threading.Thread(target=widget.thread_func)
            live_thread.start()
        elif(self.ckbLive_state.get()==False):
            self.btnSend.config(state="normal")
            evt.set()

    #exit_flag = threading.Event()
    def thread_func(self):
        global evt
        evt = threading.Event()
        while not evt.wait(timeout=self.sclInterval_value.get()/1000):
            self.send_data()

    def update_entry_FL(self, value):
        self.entryFL.delete(0, END)
        self.entryFL.insert(END, str(value))
    def update_entry_FC(self, value):
        self.entryFC.delete(0, END)
        self.entryFC.insert(END, str(value))
    def update_entry_FR(self, value):
        self.entryFR.delete(0, END)
        self.entryFR.insert(END, str(value))
    def update_entry_RL(self, value):
        self.entryRL.delete(0, END)
        self.entryRL.insert(END, str(value))
    def update_entry_RR(self, value):
        self.entryRR.delete(0, END)
        self.entryRR.insert(END, str(value))
    def update_entry_ML(self, value):
        self.entryML.delete(0, END)
        self.entryML.insert(END, str(value))
    def update_entry_MR(self, value):
        self.entryMR.delete(0, END)
        self.entryMR.insert(END, str(value))
    def update_entry_Load(self, value):
        self.entryLoad.delete(0, END)
        self.entryLoad.insert(END, str(value))
    def update_entry_Ping(self, value):
        self.entryPing.delete(0, END)
        self.entryPing.insert(END, str(value))

    def receive_data(entry_widget):
        print("receiving...")
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.bind((RootbotWidget.HOST, RootbotWidget.PORT))
                s.listen(1)
                while True:
                    conn, addr = s.accept()
                    with conn:
                        print(f'Receiver Connected by {addr}')
                        while True:
                            data = conn.recv(1024)
                            if not data: break
                            print(f"Received data: {str(data)}")
                            if [ RootbotWidget.HOST == 'localhost' ]:
                                print("Is local!")
                                s.send(data)
                s.close()
                s = None
        except Exception as e:
            print(f"An error occurred: {str(e)}")
            s.close()
            s = None

    def send_data(self):
        data = json.dumps([[self.entryFL.get(), self.entryFC.get(), self.entryFR.get(), self.entryRL.get(), self.entryRR.get()], [
            self.entryPing.get(), self.ckbCS_state.get()], [self.entryML.get(), self.entryMR.get()], self.entryLoad.get()]).replace(" ", "")
        self.txtResponse.config(state="normal")
        self.txtResponse.insert(END, "\nSending: " + data)
        self.txtResponse.config(state="disabled")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            try:
                s.connect((RootbotWidget.ADDR, RootbotWidget.PORT))
                s.send(data.encode('utf-8'))
                recv_data = s.recv(1024)
                self.txtResponse.config(state="normal")
                self.txtResponse.insert(END, "\nReceived: " + bytes(recv_data).hex() + "\n")
                self.txtResponse.insert(END, "\nReceived: " + bytes("recv_data",'utf-8').hex() + "\n")
                self.txtResponse.see(tk.END)
                self.txtResponse.config(state="disabled")
            except Exception as e:
                print("Error: Cannot send data to counterpart: \n   " + str(e))
        s.close()
        s=None

if __name__ == "__main__":
    root = tk.Tk()
    widget = RootbotWidget(root)
    widget.pack(expand=True, fill="both")
    recv_thread = threading.Thread(target=widget.receive_data).start()
    root.mainloop()

import socket
import json
import tkinter as tk
import threading


def send_json_data(data, host, port):
    try:
        # Create a socket object
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect to the recipient
        sock.connect((host, port))

        # Convert the array of integers to a JSON string
        json_data = json.dumps(data)

        # Send the JSON data to the recipient
        sock.sendall(json_data.encode('utf-8'))

        print(f"Sent data to {host}:{port}: {json_data}")

        # Close the socket
        sock.close()

    except Exception as e:
        print(f"Error: {str(e)}")


def poll_data(host, port):
    window = tk.Tk()
    window.title("Data Relay")

    relay_button = tk.Button(
        window, text="Receive and Relay Data", command=receive_and_send_data)
    relay_button.pack()

    window.mainloop()


def get_input_value():
    data = input_entry.get()
    print(f"Input value: {data}")
    root.destroy()


def receive_and_send_data():
    try:
        # Create a socket for receiving data from a remote source
        receive_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        receive_socket.bind(("localhost", 12345))  # Bind to a local port
        receive_socket.listen(1)
        print("Waiting for a connection...")
        source_conn, source_address = receive_socket.accept()
        print(f"Connected to {source_address}")

        # Create a socket for sending data to a recipient
        recipient_host = 'localhost'  # Replace with the recipient's hostname or IP address
        recipient_port = 12345  # Replace with the recipient's port number
        send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        send_socket.connect((recipient_host, recipient_port))
        print(f"Connected to recipient at {recipient_host}:{recipient_port}")

        # Receive data from the remote source
        data = source_conn.recv(1024)

        # Send the received data to the recipient
        send_socket.sendall(data)

        source_conn.close()
        send_socket.close()

    except Exception as e:
        print(f"Error: {str(e)}")


if __name__ == '__main__':
    # Replace with the recipient's hostname or IP address
    recipient_host = 'localhost'
    recipient_port = 12345  # Replace with the recipient's port number

    data = [1, 2, 3, 4, 5]  # Replace this with your array of integers

    poll_thread = threading.Thread(
        target=poll_data, args=(recipient_host, recipient_port))

    # Create the main window
    root = tk.Tk()
    root.title("Data Sender")

    # Create an input field
    input_label = tk.Label(root, text="Input:")
    input_label.pack()
    input_entry = tk.Entry(root)
    input_entry.pack()

    # Create a button to send data
    send_button = tk.Button(root, text="Send Data", command=get_input_value)
    send_button.pack()

    # Start the main loop
    root.mainloop()

    # Start the thread
    # TODO: start thread for listening
    #       tigger send procedure
    #       in thread catch data and resamble it onto stdio
    #       send catched data back to origin (after printing it out for cornfirmation)
    poll_thread.start()

    send_json_data(data, recipient_host, recipient_port)

import tkinter as tk
import serial
import time

BAUDRATE = 9600
ARDUINO_PORT = 'COM8'
TITLE = "SCARA Robot Controller"

class SimpleGUI:
    def __init__(self, root):
        self.root = root
        self.root.title(TITLE)
        self.root.configure(bg='gray')  # Set the background color to gray

        self.serial_port = ARDUINO_PORT  # Change this to your Arduino port
        self.baud_rate = BAUDRATE
        self.arduino = serial.Serial(self.serial_port, self.baud_rate, timeout=1)
        time.sleep(2)  # Wait for the serial connection to initialize

        # Create labels and entry widgets for X, Y, Z positions
        self.create_entry('X Position:', 0)
        self.create_entry('Y Position:', 1)
        self.create_entry('Z Position:', 2)

        # Create a send coordinates button
        self.send_button = tk.Button(self.root, text="Send X, Y, and Z", command=self.send_positions, bg='lightgray')
        self.send_button.grid(row=4, column=1, pady=10)

        # Create a homing button
        self.home_button = tk.Button(self.root, text="Home", command=self.send_home, bg='lightgray')
        self.home_button.grid(row=4, column=0, pady=10)

        # Create a slider for 0-255 range
        self.slider_label = tk.Label(self.root, text="Slider Value (0-255):", bg='gray', fg='white')
        self.slider_label.grid(row=5, column=0, padx=10, pady=10)
        self.slider = tk.Scale(self.root, from_=0, to=255, orient='horizontal', command=self.send_slider, bg='gray', fg='white')
        self.slider.grid(row=5, column=1, padx=10, pady=10)

    def create_entry(self, label_text, row):
        label = tk.Label(self.root, text=label_text, bg='gray', fg='white')
        label.grid(row=row, column=0, padx=10, pady=10)
        entry = tk.Entry(self.root, bg='white')
        entry.grid(row=row, column=1, padx=10, pady=10)
        setattr(self, f'entry_{row}', entry)

    def send_positions(self):
        x = self.entry_0.get()
        y = self.entry_1.get()
        z = self.entry_2.get()
        command = f"POSITION:X={x},Y={y},Z={z}\n"
        self.arduino.write(command.encode())

    def send_home(self):
        self.arduino.write(b"HOME\n")

    def send_slider(self, value):
        command = f"SLIDER:{value}\n"
        self.arduino.write(command.encode())

    def on_closing(self):
        self.arduino.close()
        self.root.destroy()



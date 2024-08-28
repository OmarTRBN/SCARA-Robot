import tkinter as tk
import serial

# Set up the serial connection
ser = serial.Serial('COM11', 9600)  # Replace with your Arduino's port

# Function to send a command to the Arduino
def send_command(command):
    ser.write(command.encode() + b'\n')

# Function to handle the "SETSPEED" command
def set_speed():
    x_speed = int(x_speed_entry.get())
    y_speed = int(y_speed_entry.get())
    z_speed = int(z_speed_entry.get())
    a_speed = int(a_speed_entry.get())
    command = f"SETSPEED:{x_speed},{y_speed},{z_speed},{a_speed}"
    send_command(command)

# Function to handle the "SETACCELERATION" command
def set_acceleration():
    x_accel = int(x_accel_entry.get())
    y_accel = int(y_accel_entry.get())
    z_accel = int(z_accel_entry.get())
    a_accel = int(a_accel_entry.get())
    command = f"SETACCELERATION:{x_accel},{y_accel},{z_accel},{a_accel}"
    send_command(command)

# Function to handle the "HOME" command
def home_motors():
    command = "HOME"
    send_command(command)

# Function to handle the "MOVETO" command
def move_to():
    x_pos = int(x_pos_entry.get())
    y_pos = int(y_pos_entry.get())
    z_pos = int(z_pos_entry.get())
    a_pos = int(a_pos_entry.get())
    command = f"MOVETO:{x_pos},{y_pos},{z_pos},{a_pos}"
    send_command(command)

# Function to handle the "PRINT" command
def print_values():
    command = "PRINT"
    send_command(command)
    
    # Read the response from the Arduino
    x_speed = ser.readline().decode().strip().split(': ')[1].split(',')[0]
    x_accel = ser.readline().decode().strip().split(': ')[1].split(',')[1]
    y_speed = ser.readline().decode().strip().split(': ')[1].split(',')[0]
    y_accel = ser.readline().decode().strip().split(': ')[1].split(',')[1]
    z_speed = ser.readline().decode().strip().split(': ')[1].split(',')[0]
    z_accel = ser.readline().decode().strip().split(': ')[1].split(',')[1]
    a_speed = ser.readline().decode().strip().split(': ')[1].split(',')[0]
    a_accel = ser.readline().decode().strip().split(': ')[1].split(',')[1]
    
    # Update the GUI elements
    x_speed_label.config(text=f"X Speed: {x_speed}")
    x_accel_label.config(text=f"X Acceleration: {x_accel}")
    y_speed_label.config(text=f"Y Speed: {y_speed}")
    y_accel_label.config(text=f"Y Acceleration: {y_accel}")
    z_speed_label.config(text=f"Z Speed: {z_speed}")
    z_accel_label.config(text=f"Z Acceleration: {z_accel}")
    a_speed_label.config(text=f"A Speed: {a_speed}")
    a_accel_label.config(text=f"A Acceleration: {a_accel}")

# Create the main window
root = tk.Tk()
root.title("Motor Control")

# Create the GUI elements
x_speed_label = tk.Label(root, text="X Speed: ")
y_speed_label = tk.Label(root, text="Y Speed: ")
z_speed_label = tk.Label(root, text="Z Speed: ")
a_speed_label = tk.Label(root, text="A Speed: ")

x_accel_label = tk.Label(root, text="X Acceleration: ")
y_accel_label = tk.Label(root, text="Y Acceleration: ")
z_accel_label = tk.Label(root, text="Z Acceleration: ")
a_accel_label = tk.Label(root, text="A Acceleration: ")

x_speed_entry = tk.Entry(root)
y_speed_entry = tk.Entry(root)
z_speed_entry = tk.Entry(root)
a_speed_entry = tk.Entry(root)

x_accel_entry = tk.Entry(root)
y_accel_entry = tk.Entry(root)
z_accel_entry = tk.Entry(root)
a_accel_entry = tk.Entry(root)

set_speed_button = tk.Button(root, text="Set Speed", command=set_speed)
set_accel_button = tk.Button(root, text="Set Acceleration", command=set_acceleration)
home_button = tk.Button(root, text="Home", command=home_motors)
move_button = tk.Button(root, text="Move", command=move_to)
print_button = tk.Button(root, text="Print Values", command=print_values)

# Arrange the GUI elements
x_speed_label.grid(row=0, column=0)
x_speed_entry.grid(row=0, column=1)
y_speed_label.grid(row=1, column=0)
y_speed_entry.grid(row=1, column=1)
z_speed_label.grid(row=2, column=0)
z_speed_entry.grid(row=2, column=1)
a_speed_label.grid(row=3, column=0)
a_speed_entry.grid(row=3, column=1)
set_speed_button.grid(row=4, column=0, columnspan=2)

x_accel_label.grid(row=5, column=0)
x_accel_entry.grid(row=5, column=1)
y_accel_label.grid(row=6, column=0)
y_accel_entry.grid(row=6, column=1)
z_accel_label.grid(row=7, column=0)
z_accel_entry.grid(row=7, column=1)
a_accel_label.grid(row=8, column=0)
a_accel_entry.grid(row=8, column=1)
set_accel_button.grid(row=9, column=0, columnspan=2)

home_button.grid(row=10, column=0)
move_button.grid(row=10, column=1)
print_button.grid(row=11, column=0, columnspan=2)

# Start the main loop
root.mainloop()
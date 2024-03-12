import serial
import time

# Define the serial port and baud rate
serial_port = "/dev/ttyACM0"  # Change this to the appropriate serial port on your system
baud_rate = 115200  # This should match the baud rate of your printer

# Open the serial connection
ser = serial.Serial(serial_port, baud_rate, timeout=1)

# Wait for the connection to be established (optional)
time.sleep(2)

# Example G-code command to move the print head to the home position
gcode_command = "G1 X0 Y0\n"  # G28 is the command for homing

# Send the G-code command
ser.write(gcode_command.encode())

# Wait for the printer to process the command (adjust as needed)
time.sleep(2)

# Read and print the response from the printer (optional)
response = ser.readline().decode().strip()
print("Printer response:", response)

# Close the serial connection
ser.close()

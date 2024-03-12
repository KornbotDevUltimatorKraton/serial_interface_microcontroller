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
#gcode_command = "G28\n"
#gcode_command = "M73\n"
#gcode_command2 = "M211\n"  # 57.3 G28 is the command for homing
#gcode_command3 = "M18\n"
# Send the G-code command
#gcode_command = "M104 S210 T0\n"
#gcode_command = "M211\n"
#gcode_command = "G92 X0 Y0 Z0"
#while True:
#gcode_command = "M105 T0\n"
#gcode_command = "M106 P0 S\n"
gcode_command = "M587 S'Idatabots' P'Rkl3548123#'' 123'"
ser.write(gcode_command.encode())
#gcode_command3 = "M18\n"
#ser.write(gcode_command2.encode())
#ser.write(gcode_command3.encode())
# Wait for the printer to process the command (adjust as needed)
time.sleep(1)
# Read and print the response from the printer (optional)
response = ser.readline().decode('utf-8').strip()
print("Printer response:", response)
# Close the serial connection
ser.close()

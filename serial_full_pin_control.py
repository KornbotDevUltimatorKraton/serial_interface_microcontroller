import json
import time
import serial 
import requests 
from itertools import count
# Open the serial port, update 'COMx' with your Arduino port
ser = serial.Serial('/dev/ttyUSB0', 115200)  #, timeout=0.0132)

for i in count(0): 
    try:
      # Send the JSON string
      for i in range(0,255):
         json_data = {"Analog_input":"PA0","pwm_control":{"PB3":i,"PB4":i,"PB5":i,"PB9":i},"servo_control":{"PB14":30}}
         #json_data = {"key":"sensor1","value":90}
         json_string = json.dumps(json_data)
         ser.write((json_string+"\n").encode())  # 
         #print((json_string).encode())
         angle_data = ser.readline().decode().strip()
         print(angle_data)
         
         #json_data['value'] = angle_data
         # Close the serial port
    except:
      pass 



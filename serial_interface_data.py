import json
import time
import serial 
import requests 
from itertools import count
# Open the serial port, update 'COMx' with your Arduino port
ser = serial.Serial('/dev/ttyUSB0', 115200) 

for i in count(0): 
    try:
      # Send the JSON string
      for i in range(0,256):
         json_data = {"Analog_input":{"PA0":"analog","PA1":"analog","PA2":"analog","PA3":"analog","PA4":"analog","PA5":"analog","PA6":"analog","PA7":"analog"},"pwm_control":{"PB3":i,"PB4":i,"PB5":i,"PB9":i},"servo_control":{"PB14":30,"PB15":30}}
         #json_data = {'Analog_input':['PA0','PA1','PA2','PA3','PA4'],'pwm_control':['PB3','PB4'],'servo_control':['PB14','PB15']}
         #json_data = {"key":"sensor1","value":90}
         json_string = json.dumps(json_data)
         ser.write((json_string+"\n").encode())  # 
         #print((json_string).encode())
         angle_data = ser.readline().decode().strip()
         #print(angle_data,type(angle_data))
         json_transform = json.loads(angle_data) # Get the json data transform 
         print(json_transform,type(json_transform))
         print("Get PA0 ",json_transform['PA0'])  
         #json_data['value'] = angle_data
         # Close the serial port
    except:
      pass 
#ser.close()


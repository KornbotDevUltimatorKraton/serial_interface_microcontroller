/*
Author: Roboreactor_firmware_generator
Project_name:Smart_robots
Date:2024-01-18 12:19:54.652122
*/
#include <Servo.h>
#include <ArduinoJson.h>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int analog_0 = 0;
int analog_1 = 0;
int analog_2 = 0;
int analog_3 = 0;
int analog_4 = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Servo Servo_PB14;
Servo Servo_PB15;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
JsonDocument analoginput;
void setup(){
		Serial.begin(115200);
    Serial.print("Devices ready!");
    pinMode(LED_BUILTIN,OUTPUT);
		Servo_PB14.attach(PB14);
		Servo_PB15.attach(PB15);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		analoginput["mcus"] = "STM32F103C8T6";
		analoginput["project"] = "Smart_robots";
		analoginput["Components"] = "Main_component";
}
void loop(){
		if(Serial.available() > 0){
			JsonDocument doc;
      digitalWrite(PC13, HIGH);
			String jsonString = Serial.readStringUntil('\n');
			const char *jsonChars = jsonString.c_str();
			DeserializationError error = deserializeJson(doc, jsonChars);
			if (error){
				Serial.print(F("deserializeJson() failed: "));
				HAL_NVIC_SystemReset();
				Serial.println(error.f_str());
				return;
			}
      //These 3 functions need to be in FreeRTOS 
			const char* sensor = doc["Analog_input"];
			if(doc.containsKey("Analog_input")){
				JsonObject analog_pin = doc["Analog_input"].as<JsonObject>();
				for (JsonPair kv : analog_pin){
					const char* key = kv.key().c_str();
					int value = kv.value().as<int>();
					pin_configuretion(key,value,"Analog_input");
				}
			}
			const char* pwm_pin = doc["pwm_control"];
			if(doc.containsKey("pwm_control")){
				JsonObject pwm_pin = doc["pwm_control"].as<JsonObject>();
				for (JsonPair kv : pwm_pin){
					const char* key = kv.key().c_str();
					int value = kv.value().as<int>();
					pin_configuretion(key,value,"pwm_control");
				}
			}
			const char* servo_pin = doc["servo_control"];
			if(doc.containsKey("servo_control")){
				JsonObject servo_pin = doc["servo_control"].as<JsonObject>();
				for (JsonPair kv : servo_pin){
					const char* key = kv.key().c_str();
					int value = kv.value().as<int>();
					pin_configuretion(key,value,"servo_control");
				}
			}
		else{
			Serial.println("No key JSON data.");
		}
    
		String SensorString;
		serializeJson(analoginput,SensorString);
		Serial.println(SensorString);
    digitalWrite(PC13, LOW);
		}
  
}
void pin_configuretion(String key, int value_control,String function_pin){
		if(function_pin == "Analog_input"){
			if(String(key) == "PA0"){
				analog_0 = analogRead(PA0);
				analoginput[key] = analog_0;
			}
			if(String(key) == "PA1"){
				analog_1 = analogRead(PA1);
				analoginput[key] = analog_1;
			}
			if(String(key) == "PA2"){
				analog_2 = analogRead(PA2);
				analoginput[key] = analog_2;
			}
			if(String(key) == "PA3"){
				analog_3 = analogRead(PA3);
				analoginput[key] = analog_3;
			}
			if(String(key) == "PA4"){
				analog_4 = analogRead(PA4);
				analoginput[key] = analog_4;
			}
		}
		if(function_pin == "pwm_control"){
      
			if(String(key) == "PB3"){
				analogWrite(PB3,value_control);
			}
			if(String(key) == "PB4"){
				analogWrite(PB4,value_control);
			}

		}
		if(function_pin == "servo_control"){
			if(String(key) == "PB14"){
				Servo_PB14.write(value_control);
			}
			if(String(key) == "PB15"){
				Servo_PB15.write(value_control);
			}

		}
}

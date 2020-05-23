import serial
import paho.mqtt.client as mqtt

BROKER = "mqtt.eclipse.org"
CLIENTID = "MQTTExample"
TOPIC_ONE = "A507/sensors/pokret"
QOS = 1

import time

mqttc = mqtt.Client(CLIENTID)
mqttc.connect(BROKER)

ser = serial.Serial(COMPORT, 115200, timeout=5) 
while True:
	message = ser.readline().decode()
	print (message)
	if "P:" in message:
		string, pokret = message.split(" ")
		mqttc.publish(TOPIC_ONE, payload=pokret, qos=QOS, retain=False)

	time.sleep(0.01)
mqttc.disconnect()
time.sleep(1)

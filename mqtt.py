import paho.mqtt.client as mqtt
from time import sleep
from random import randrange

broker_address = "broker.hivemq.com"
broker_port = 1883
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)
client.connect(broker_address, broker_port)

while True:
  numData = 220
  strData = "Hello"

  client.publish("/kalil/str", str(strData))
  client.publish("/kalil/num", str(numData))
  
  print(f"Data yang akan dikirim : \nData Numerik = {numData}, Data String = {numData}")
  sleep(10)

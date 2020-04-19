import sys
import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
import  time

broker="192.168.1.51"

def on_message(client, userdata, message):
   msg=str(message.payload.decode("utf-8"))
   #print("message =",msg)
   topic=message.topic
   messages.append([topic,msg])
def on_connect(client, userdata, flags, rc):

    if rc==0:
        client.connected_flag=True
        client.subscribe(sub_topic)
    else:
        client.bad_connection_flag=True
        client.connected_flag=False

messages=[]
sub_topic="resetcount"
client= mqtt.Client("GPIO-client-001")

client.on_message=on_message
client.on_connect=on_connect
client.connected_flag=False
client.connect(broker)

GPIO.cleanup()
clk = 20


GPIO.setmode(GPIO.BCM)
GPIO.setup(clk, GPIO.IN, pull_up_down=GPIO.PUD_UP)
counter = 0
clkLastState = GPIO.input(clk)

while True:
    client.loop(0.001)
    clkState = GPIO.input(clk)
    if clkState != clkLastState:
        counter += 1
        if counter % 100 == 0:
            client.publish("position",counter)
            print("Position: ",counter)

    clkLastState = clkState
        
    if len(messages)>0:
        m=messages.pop(0)
        print("received ",m)
        if int(m[1]) == 1:
            counter = 0
        
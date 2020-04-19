#! c:\python34\python3
#!/usr/bin/env python
##demo code provided by Steve Cope at www.steves-internet-guide.com
##email steve@steves-internet-guide.com
##Free to use for any purpose
##If you like and use this code you can
##buy me a drink here https://www.paypal.me/StepenCope
import sys
import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
import  time

#broker="test.mosquitto.org"
broker="192.168.1.51"
#define callback
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

cpio_channels=[4,5,6,12,13,16,17,18,19,20,21,22,23,24,25,26,27]# base channels
print("using ",sys.version) #what version of python
mode=GPIO.getmode()
print("mode is ",mode)
GPIO.setmode(GPIO.BCM)
mode=GPIO.getmode()
print("mode is ",mode)
GPIO.setup(4,GPIO.OUT)
GPIO.output(4,1)
print("value is ",GPIO.input(4))
GPIO.setup(5,GPIO.IN)
print("input value is ",GPIO.input(5))
#GPIO.cleanup()
print("board ",GPIO.BOARD)
print("bcm ",GPIO.BCM)

##MQTT
messages=[]
sub_topic="ledstatus"
client= mqtt.Client("GPIO-client-001")  #create client object client1.on_publish = on_publish                          #assign function to callback client1.connect(broker,port)                                 #establish connection client1.publish("house/bulb1","on")  
######
client.on_message=on_message
client.on_connect=on_connect
client.connected_flag=False
client.connect(broker)#connect
while True:
    client.loop(0.001)
    client.publish("intstatus",GPIO.input(4))
    print("intstatus ",GPIO.input(4))

    if len(messages)>0:
        m=messages.pop(0)
        print("received ",m)
        GPIO.output(4,int(m[1])) #set
        print("value is ",GPIO.input(4))
        
    

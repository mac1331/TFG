import sys
import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as sub
import  time

broker="192.168.1.51"
realpos = 0
def on_message_print(client, userdata, message):
#     print(str(message.topic), str(message.payload))
    global realpos
    realpos = int(message.payload)/100
#     print("jkbfsajrbbf    ",realpos)
          
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
sub_topic="position"
client= mqtt.Client("GPIO-client-004")

client.on_message=on_message
client.on_connect=on_connect
client.connected_flag=False
client.connect(broker)
# sub.callback(on_message_print, sub_topic, hostname=broker)
client.message_callback_add(sub_topic, on_message_print)
client.loop_start()

GPIO.cleanup()
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.OUT)    # set GPIO 25 as output for the PWM signal
D2A = GPIO.PWM(20, 10000)    # create object D2A for PWM on port 25 at 1KHz
D2A.start(0)                # start the PWM with a 0 percent duty cycle (off)
dutycycle = 0
p = 10
i = 0
d = 0
realpos = 0
error = 10000000
client.publish("resetcount",1)
print("aquitoy")
try:

    while True:
#         client.loop(100)
        desiredpos = int(input('Enter a position to go: '))
        client.publish("resetcount",1)
        print ('Desired position is: : {0}%'.format(desiredpos))
        while error > 0:
            error = desiredpos - realpos
            time.sleep(0.2)
            dutycycle = error*p
            if dutycycle >= 100:
                dutycycle = 100
            print (realpos)
            D2A.ChangeDutyCycle(dutycycle)

except (KeyboardInterrupt, ValueError, Exception) as e:
    print(e)
    D2A.stop()     # stop the PWM output
    GPIO.cleanup() # clean up GPIO on CTRL+C exit














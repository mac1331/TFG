import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as sub
import time
from simple_pid import PID
import math

##PID configurations
pidMDRT = PID(1, 0.05, 0, 0)
pidMESQ = PID(1, 0.05, 0, 0)
pidPy = PID(15, 0.7, 0.1, 0)
pidPx = PID(7, 0.7, 0.1, 0)

pidMDRT.sample_time = 0.1
pidMESQ.sample_time = 0.1
pidPy.sample_time = 0.01
pidPx.sample_time = 0.01

pidMDRT.output_limits = (-100, 100)
pidMESQ.output_limits = (-100, 100)
pidPy.output_limits = (-100, 100)
pidPx.output_limits = (-100, 100)

pidPy.auto_mode = True
pidPx.auto_mode = True
pidMDRT.auto_mode = True
pidMESQ.auto_mode = True

broker="192.168.1.51"
RposY = 0
RposX = 0

def lost(client, userdata, message):
    messages.append([message.topic,str(message.payload.decode("utf-8"))])
    ESQ.ChangeDutyCycle(0)
    DRT.ChangeDutyCycle(0)
#     print(RposX)
def on_message_posX(client, userdata, message):
    messages.append([message.topic,str(message.payload.decode("utf-8"))])
    if message.topic == "positionX":
        global RposX
        RposX = int(message.payload)

def on_message_posY(client, userdata, message):
    messages.append([message.topic,str(message.payload.decode("utf-8"))])
    if message.topic == "positionY":
        global RposY
        RposY = int(message.payload)
#     print(RposY)
def on_message(client, userdata, message):
   msg=str(message.payload.decode("utf-8"))
   print("message =",msg)
   topic=message.topic
   messages.append([topic,msg])
def on_connect(client, userdata, flags, rc):

    if rc==0:
        client.connected_flag=True
        client.subscribe([(sub_topicy,0),(sub_topicx,0),("ObjectLost",0)])
    else:
        client.bad_connection_flag=True
        client.connected_flag=False

messages=[]
sub_topicx="positionX" ##/"positionY"
sub_topicy="positionY"
client= mqtt.Client("motors")

client.on_message=on_message
client.on_connect=on_connect
client.connected_flag=False
client.connect(broker)
client.message_callback_add(sub_topicx, on_message_posX)
client.message_callback_add(sub_topicy, on_message_posY)
client.message_callback_add("ObjectLost", lost)


client.loop_start()


GPIO.cleanup()
time.sleep(0.1)
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)    
GPIO.setup(12, GPIO.OUT)    
GPIO.setup(24, GPIO.OUT)    
GPIO.setup(23, GPIO.OUT)    
GPIO.setup(18, GPIO.OUT)
ESQ = GPIO.PWM(20, 1000)
DRT = GPIO.PWM(18, 1000)
ESQ.start(0) 
DRT.start(0) 
dutyESQ = 100
dutyDRT = 100
pidx = 0
pidy = 0
mod = 1
try:
    while True:
        if mod:
            mod = 0
            X2go = 150 #int(input('Enter a position X to go: '))
            Y2go = 130 #int(input('Enter a position Y to go: '))
#             ESQ.ChangeDutyCycle(dutyESQ)
#             DRT.ChangeDutyCycle(dutyDRT)
            pidPx.setpoint = X2go
            pidPy.setpoint = Y2go
            
        pidx = -pidPx(RposX)   ###########################crec que es aixi perque la camara esta girada# # # # # # # # #   
        pidy = pidPy(RposY)       
        pidMDRT.setpoint = pidy*math.sin(70) + pidx*math.cos(70)
        pidMESQ.setpoint = pidy*math.sin(70) - pidx*math.cos(70)
#         dutyDRT = pidy*math.sin(70) + pidx*math.cos(70)
#         dutyESQ = pidy*math.sin(70) - pidx*math.cos(70)
        dutyDRT = pidMDRT(dutyDRT)
        dutyESQ = pidMESQ(dutyESQ)
        
        print("ERRORs= ",X2go-RposX, Y2go-RposY,"PIDs=", pidx, pidy,"REALPOS=", RposX, RposY,"DUTYs=", dutyESQ, dutyDRT)
#         time.sleep(1)
        
        if dutyDRT > 100:
            dutyDRT = 100
        if dutyDRT < -100:
            dutyDRT = -100
        if dutyESQ > 100:
            dutyESQ = 100
        if dutyESQ < -100:
            dutyESQ = -100
        
        if (int(dutyESQ) >= 0):
            GPIO.output(16,GPIO.HIGH)
            GPIO.output(12,GPIO.LOW)
        
        else:
            GPIO.output(16,GPIO.LOW)
            GPIO.output(12,GPIO.HIGH)
        
        if (int(dutyDRT) >= 0):
            GPIO.output(24,GPIO.LOW)
            GPIO.output(23,GPIO.HIGH)
        else:
            GPIO.output(24,GPIO.HIGH)
            GPIO.output(23,GPIO.LOW)

        ESQ.ChangeDutyCycle(abs(dutyESQ))
        DRT.ChangeDutyCycle(abs(dutyDRT))

except (KeyboardInterrupt, ValueError, Exception) as e:
    print(e)
    ESQ.stop()     # stop the PWM output
    DRT.stop()     # stop the PWM output
    GPIO.cleanup() # clean up GPIO on CTRL+C exit


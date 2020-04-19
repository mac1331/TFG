import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as sub
import time
from simple_pid import PID

##PID configurations
# pidMDRT = PID(1, 0.1, 0.05, stepoint = 0)
# pidMESQ = PID(1, 0.1, 0.05, stepoint = 0)
# pidPy = PID(1, 0.1, 0.05, stepoint = 0)
# 
# pidMDRT.sample_time = 0.01
# pidMESQ.sample_time = 0.01
# pidPy.sample_time = 0.01
# 
# pidMDRT.output_limits = (-100, 100)
# pidMESQ.output_limits = (-100, 100)
# 
# pidPy.auto_mode = False
# pidMDRT.auto_mode = True
# pidMESQ.auto_mode = True

broker="192.168.1.51"
RposY = 0
def on_message_print(client, userdata, message):
#     print(str(message.topic), str(message.payload))
    global RposY
    RposY = float(message.payload)
#     print("RposY    ",RposY)
          
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
sub_topic="positionY"
client= mqtt.Client("motors")

client.on_message=on_message
client.on_connect=on_connect
client.connected_flag=False
client.connect(broker)
client.message_callback_add(sub_topic, on_message_print)
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
mod = 1
try:
    while True:
#         X2go = input('Enter a position X to go: ')
        if mod:
            mod = 0
            Y2go = int(input('Enter a position Y to go: '))
            ESQ.ChangeDutyCycle(dutyESQ)
            DRT.ChangeDutyCycle(dutyDRT)

#         pidPy.setpoint(Y2go)
        if (Y2go >= int(RposY)):
            GPIO.output(16,GPIO.HIGH)
            time.sleep(0.1)
            GPIO.output(12,GPIO.LOW)
            time.sleep(0.1)
            GPIO.output(24,GPIO.LOW)
            time.sleep(0.1)
            GPIO.output(23,GPIO.HIGH)
            print("DOWN")
        else:
            GPIO.output(16,GPIO.LOW)
            time.sleep(0.1)
            GPIO.output(12,GPIO.HIGH)
            time.sleep(0.1)
            GPIO.output(24,GPIO.HIGH)
            time.sleep(0.1)
            GPIO.output(23,GPIO.LOW)
            print("UP")

        
except (KeyboardInterrupt, ValueError, Exception) as e:
    print(e)
    ESQ.stop()     # stop the PWM output
    DRT.stop()     # stop the PWM output
    GPIO.cleanup() # clean up GPIO on CTRL+C exit


import RPi.GPIO as GPIO
from time import sleep
 
GPIO.setmode(GPIO.BCM)
 
Motor1 = 16    # Input Pin
Motor2 = 12    # Input Pin
Motor3 = 20    # Enable Pin
 
GPIO.setup(Motor1,GPIO.OUT)
GPIO.setup(Motor2,GPIO.OUT)
GPIO.setup(Motor3,GPIO.OUT)
 
D2A = GPIO.PWM(Motor3, 1000)    # create object D2A for PWM on port 25 at 1KHz
D2A.start(50)                # start the PWM with a 0 percent duty cycle (off)
 
print ("FORWARD MOTION")
GPIO.output(Motor1,GPIO.HIGH)
GPIO.output(Motor2,GPIO.LOW)
for e in range(30,101):
    D2A.ChangeDutyCycle(e)
    sleep(0.1)
    print (e)
sleep(10)

for e in range(100,20,-1):
    D2A.ChangeDutyCycle(e)
    sleep(0.5)
sleep(1)

print ("BACKWARD MOTION")
GPIO.output(Motor2,GPIO.HIGH)
GPIO.output(Motor1,GPIO.LOW)
for e in range(30,101):
    D2A.ChangeDutyCycle(e)
    sleep(0.2)
sleep(1)

for e in range(100,20,-1):
    D2A.ChangeDutyCycle(e)
    sleep(0.2)

# GPIO.output(Motor3,GPIO.HIGH)
 
# GPIO.output(Motor3,GPIO.HIGH)
 
# D2A.ChangeDutyCycle(0)
# sleep(1)
# 
# print ("BACKWARD MOTION")
# GPIO.output(Motor1,GPIO.LOW)
# GPIO.output(Motor2,GPIO.HIGH)
# for e in range(100,0,-1):
#     D2A.ChangeDutyCycle(e)
#     sleep(0.1)# GPIO.output(Motor3,GPIO.HIGH)
#  
#  
print ("STOP")
D2A.ChangeDutyCycle(0)
sleep(1)

GPIO.cleanup()

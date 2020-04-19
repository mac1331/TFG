import RPi.GPIO as GPIO
import time


GPIO.cleanup()
time.sleep(2)
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)    
GPIO.setup(12, GPIO.OUT)    
GPIO.setup(24, GPIO.OUT)    
GPIO.setup(23, GPIO.OUT)    
GPIO.setup(18, GPIO.OUT)
ESQ = GPIO.PWM(20, 501)
DRT = GPIO.PWM(18, 500)
dutyESQ = 70
dutyDRT = 70
GPIO.output(16,GPIO.HIGH)
time.sleep(0.1)
GPIO.output(12,GPIO.LOW)
time.sleep(0.1)
GPIO.output(24,GPIO.LOW)
time.sleep(0.1)
GPIO.output(23,GPIO.HIGH)
print("up")
ESQ.start(100) 
DRT.start(100)
time.sleep(0.1)

for e in range(40,101):
    ESQ.ChangeDutyCycle(e)
    DRT.ChangeDutyCycle(e)
    time.sleep(0.1)
    print (e)
time.sleep(5)
for e in range(100,20,-1):
    ESQ.ChangeDutyCycle(e)
    DRT.ChangeDutyCycle(e)
    time.sleep(0.1)
    print (e)
time.sleep(1)

GPIO.output(16,GPIO.LOW)
time.sleep(0.1)
GPIO.output(12,GPIO.HIGH)
time.sleep(0.1)
GPIO.output(24,GPIO.HIGH)
time.sleep(0.1)
GPIO.output(23,GPIO.LOW)
print("UP")

ESQ.ChangeDutyCycle(100)
DRT.ChangeDutyCycle(100)
time.sleep(0.1)
for e in range(40,101):
    ESQ.ChangeDutyCycle(e)
    DRT.ChangeDutyCycle(e)
    time.sleep(0.1)
    print (e)
time.sleep(1)
for e in range(100,20,-1):
    ESQ.ChangeDutyCycle(e)
    DRT.ChangeDutyCycle(e)
    time.sleep(0.1)
    print (e)
time.sleep(1)
ESQ.stop()     # stop the PWM output
DRT.stop()
GPIO.cleanup()

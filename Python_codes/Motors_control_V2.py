from pynput import keyboard
from pynput.keyboard import Key
import RPi.GPIO as GPIO
import time


def lef(event = None):
    GPIO.output(16,GPIO.HIGH)
    GPIO.output(12,GPIO.LOW)
    GPIO.output(24,GPIO.HIGH)
    GPIO.output(23,GPIO.LOW)
    ESQ.ChangeDutyCycle(abs(100))
    DRT.ChangeDutyCycle(abs(100))
    time.sleep(0.5)
    ESQ.start(0) 
    DRT.start(0)
    
def rig(event = None):
    GPIO.output(16,GPIO.LOW)
    GPIO.output(12,GPIO.HIGH)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.HIGH)
    ESQ.ChangeDutyCycle(abs(100))
    DRT.ChangeDutyCycle(abs(100))
    time.sleep(0.5)
    ESQ.start(0) 
    DRT.start(0)
def up(event = None):
    GPIO.output(16,GPIO.HIGH)
    GPIO.output(12,GPIO.LOW)
    GPIO.output(24,GPIO.LOW)
    GPIO.output(23,GPIO.HIGH)
    ESQ.ChangeDutyCycle(abs(100))
    DRT.ChangeDutyCycle(abs(100))
    time.sleep(0.5)
    ESQ.start(0) 
    DRT.start(0)
def dw(event = None):
    GPIO.output(16,GPIO.LOW)
    GPIO.output(12,GPIO.HIGH)
    GPIO.output(24,GPIO.HIGH)
    GPIO.output(23,GPIO.LOW)
    ESQ.ChangeDutyCycle(abs(100))
    DRT.ChangeDutyCycle(abs(100))
    time.sleep(0.5)
    ESQ.start(0) 
    DRT.start(0)
def on_press(key):
    #handle pressed keys
    pass

def on_release(key):
    #handle released keys
    if(key==Key.right):
        rig()

    if(key==Key.left):
        lef()

    if(key==Key.up):
        up()

    if(key==Key.down):
        dw()
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

with keyboard.Listener(on_press=on_press,on_release=on_release) as listener:
    listener.join() 

from RPi import GPIO
import time
clk = 20
dt = 21
GPIO.setmode(GPIO.BCM)
GPIO.setup(clk, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(dt, GPIO.IN, pull_up_down=GPIO.PUD_UP)
counter = 0
speedlist = [0,0,0,0,0, 0,0,0,0,0 ,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 ,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 ,0,0,0,0,0, 0,0,0,0,0]
speed = 0.0
dtLastState = GPIO.input(dt)
try:
        while True:
                dtState = GPIO.input(dt)
                if dtState != dtLastState:
                        counter += 1
                        speedlist.append(time.time())
                        speedlist.remove(speedlist[0])
    #                                 speed = speedlist[99] - speedlist[0]
                        suma = 0
                        for i in range(1,len(speedlist)-1):
                            suma = suma + (speedlist[i] - speedlist[i-1])
                        speed = suma/(len(speedlist)-1)
                print (speed)
                dtLastState = dtState
finally:
        GPIO.cleanup()

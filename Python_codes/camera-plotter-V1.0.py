import numpy as np
import time
import cv2
import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as sub

broker="192.168.1.51"

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
client= mqtt.Client("Camera")

client.on_message=on_message
client.on_connect=on_connect
client.connected_flag=False
client.connect(broker)
# sub.callback(on_message_print, sub_topic, hostname=broker)
client.message_callback_add(sub_topic, on_message_print)
client.loop_start()




cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH,320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,240)
temps = 0
tempsant = 0 
while(True):
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.imshow('frame3',gray)
    binari,tres = cv2.threshold(gray,240,255,cv2.THRESH_BINARY)
#     kernel = np.ones((3,3),np.uint8)
    kernel = np.array(([0, 1, 1, 0],[1, 1, 1, 1],[1, 1, 1, 1],[0, 1, 1, 0]),np.uint8)
    erosion = cv2.erode(tres,kernel,iterations = 1)
    y = 0
    count = 1
    xs = 0
    ys = 0
    for fila in range(0,len(erosion),5):
        x = 0
        for col in range(20,len(erosion[0])-20,5):
            if erosion[fila][col] == 255:
                xs += fila
                ys += col
                count += 1
            x += 1
        y += 1
    tempsant = temps    
    temps = time.time()
    print(temps-tempsant,xs/count,ys/count)      
    client.publish("position",ys/count)
    
    cv2.imshow('frame1',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
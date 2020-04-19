import numpy as np
import time
import cv2

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
        
    cv2.imshow('frame1',gray)
    cv2.imshow('frame2',erosion)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
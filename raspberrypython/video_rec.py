import cv2
import time
import firebase_admin
from firebase_admin import credentials, storage


cred = credentials.Certificate("/home/pi/Downloads/raspberrykey.json")
firebase_admin.initialize_app(cred, {"storageBucket": "raspberry-b22a0.appspot.com"})
bucket = storage.bucket()

cap = cv2.VideoCapture(-1)    
if cap.isOpened:
    current_time = time.strftime("%Y%m%d%H%M%S")
    file_path = '/home/pi/record/record_{current_time}.avi'
    fps = 30.0                     
    fourcc = cv2.VideoWriter_fourcc(*'DIVX') 
    width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
    height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
    size = (int(width), int(height))                       
    out = cv2.VideoWriter(file_path, fourcc, fps, size) 
    while True:
        ret, frame = cap.read()
        if ret:
            cv2.imshow('camera-recording',frame)
            out.write(frame)                        
            if cv2.waitKey(int(1000/fps)) != -1: 
                break
        else:
            print("no frame!")
            break
    out.release()                                   
else:
    print("can't open camera!")
cap.release()
cv2.destroyAllWindows()

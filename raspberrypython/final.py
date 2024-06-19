import cv2
import socket
import time
import os
from firebase_admin import credentials, storage, initialize_app, db

HOST = '192.168.137.103'
PORT = 8080
interval = 0.5

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(0)


print(f"서버 대기 중: {HOST}:{PORT}")

client_socket, addr = server_socket.accept()
print(f"연결됨: {addr}")

def open():
    cap = cv2.VideoCapture("http://192.168.137.103:8081/?action=stream")
    
    if not cap.isOpened():
        print("카메라를 열 수 없습니다.")
        exit()

    while True:
        ret, frame = cap.read()

        cv2.imshow("video", frame)
        if cv2.waitKey(1) == 27:
            break

    cap.release()
    cv2.destroyAllWindows()

def initialize_firebase():
    cred = credentials.Certificate("/home/pi/Downloads/raspberrykey.json")
    initialize_app(cred, {"databaseURL": "https://raspberry-b22a0-default-rtdb.firebaseio.com/",
                          "storageBucket": "raspberry-b22a0.appspot.com"})
    return storage.bucket(), db.reference()

bucket, images_ref = initialize_firebase()

def capture_and_save_image():
    cap = cv2.VideoCapture("http://192.168.137.102:8081/?action=stream")
    timestamp = time.strftime("%Y%m%d%H%M%S")
    image_file = f"image_{timestamp}.jpeg"

    try:
        ret, frame = cap.read()
        cv2.imwrite(image_file, frame)
        print(f"{image_file} saved")

    finally:
        cap.release()

    return image_file

def capture_and_upload_video():
    cap = cv2.VideoCapture("http://192.168.137.102:8081/?action=stream")
    timestamp = time.strftime("%Y%m%d%H%M%S")
    video_file = f"video_{timestamp}.avi"
    out = cv2.VideoWriter(video_file, cv2.VideoWriter_fourcc(*'DIVX'), 20.0, (640,480))

    try:
        while True:
            ret, frame = cap.read()
            if not ret:
                break

            out.write(frame)
            cv2.imshow("Video Stream", frame)

            key = cv2.waitKey(1) & 0xFF
            if key == ord('s'):
                break

    finally:
        cap.release()
        out.release()
        cv2.destroyAllWindows()

    return video_file

def upload_video_to_firebase(video_file, image_file):
    try:
        blob = bucket.blob('videos/'+video_file)
        blob.upload_from_filename(video_file)
        print(f"{video_file} upload success")
        

        blob = bucket.blob('image/'+image_file)
        blob.upload_from_filename(image_file)
        print(f"{image_file} upload success")
        
        download_url = blob.public_url
        
        timerecord = int(time.time())
        images_ref.child(str(timerecord)).set({
            "download_url": download_url,
            "timerecord": timerecord
        })

    except Exception as e:
        print(f"Error occurred during upload: {e}")

    finally:
        os.remove(video_file)
        os.remove(image_file)
        
try:
    while True:        
        video_file = capture_and_upload_video()
        image_file = capture_and_save_image()
        if video_file:
            upload_video_to_firebase(video_file, image_file)
        
        time.sleep(interval)
            
except KeyboardInterrupt:
    print("Program terminated")

client_socket.close()
server_socket.close()

import cv2
import firebase_admin
import time
import os
from firebase_admin import credentials, storage, db
from ultralytics import YOLO

# Firebase 서비스 계정 키 경로
cred = credentials.Certificate("D:/yolov8/raspberrykey.json")

# Firebase 프로젝트 초기화
firebase_admin.initialize_app(cred, {
    "storageBucket": "raspberry-b22a0.appspot.com"
})

# Load a pretrained YOLOv8n model
model = YOLO('D:/yolov8/best2.pt')

# Read an image using OpenCV
video_path = "videos\dfd.mp4"
cap = cv2.VideoCapture(video_path)

if not cap.isOpened():
    print("Error: Could not open video.")
    exit()

timestamp = time.strftime("%Y%m%d%H%M%S")

d_drive_folder = 'D:/results/videos/'
local_filename = os.path.join(d_drive_folder, f'_{timestamp}.mp4')

# Firebase Storage에 저장할 파일명
storage_filename = f"video_{timestamp}.mp4"

# Firebase Storage 클라이언트
storage_client = storage.bucket()

image_folder = 'D:/results/images/'
frame_counter = 0

# 비디오의 프레임 너비와 높이 가져오기
frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv2.CAP_PROP_FPS)

fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter(local_filename, fourcc, fps, (frame_width, frame_height))

while cap.isOpened():
    # Read a frame from the video
    success, frame = cap.read()

    if success:
        # Run YOLOv8 inference on the frame
        results = model(frame, conf=0.5)

        # Visualize the results on the frame
        annotated_frame = results[0].plot()

        # Display the annotated frame
        cv2.imshow("YOLOv8 Inference", annotated_frame)

        # 비디오에 프레임 쓰기
        out.write(annotated_frame)

        for r in results:
            print(r.boxes.cls)
            if 1 in r.boxes.cls and frame_counter % 50 == 0:
                image_filename = os.path.join(image_folder, f'frame_{timestamp}_{frame_counter}.jpg')
                cv2.imwrite(image_filename, annotated_frame)
                print(f"Detected a person in frame. Image saved as {image_filename}")

                storage_path1 = 'images/'
                storage_filename1 = f'frame_{timestamp}_{frame_counter}.jpg'
                blob = storage_client.blob(storage_path1 + storage_filename1)
                blob.upload_from_filename(image_filename)
                print(f"{storage_filename1} upload success")

        frame_counter += 1
        print(f"Frame Counter: {frame_counter}")

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        # Break the loop if the end of the video is reached
        break

# 로컬에 저장된 비디오 파일을 Firebase Storage에 업로드
blob = storage_client.blob('videos/' + storage_filename)
blob.upload_from_filename(local_filename)
print(f"{storage_filename} upload success")

# 비디오 캡처 객체 해제
cap.release()
out.release()
cv2.destroyAllWindows()

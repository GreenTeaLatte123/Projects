import cv2

cap = cv2.VideoCapture("http://192.168.137.102:8081/?action=stream")

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
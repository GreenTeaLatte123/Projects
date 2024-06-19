import cv2
import time
import os

def main():
    camera = cv2.VideoCapture(-1)
    camera.set(3, 640)
    camera.set(4, 480)

    while camera.isOpened():
        _, frame = camera.read()
        cv2.imshow('Camera Capture', frame)

        key = cv2.waitKey(1)
        if key == ord('q') or key == 27:
            break
        elif key == ord('s'):  
            save_directory = "/home/pi/image/"
            capture_and_save(frame, save_directory)

    

def capture_and_save(frame, save_directory):
   
    current_time = time.strftime("%Y%m%d%H%M%S")
    filename = f"captured_image_{current_time}.png"

    
    full_path = os.path.join(save_directory, filename)
    cv2.imwrite(full_path, frame)
    print(f"Image saved as {full_path}")

if __name__ == '__main__':
    main()

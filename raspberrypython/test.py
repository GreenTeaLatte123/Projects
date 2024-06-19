import socket
import cv2
import time
import os
import final
from gpiozero import LED
from firebase_admin import credentials, storage, initialize_app, db

led = LED(17)

def control_led(command):
    if command.strip() == 'turnOn':  # 공백 제거 후 비교
        led.on()
        return 'LED 켜짐'
    elif command.strip() == 'turnOff':  # 공백 제거 후 비교
        led.off()
        return 'LED 꺼짐'
    else:
        return '올바르지 않은 명령'

host = ''
port = 8080

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(1)

print(f"서버가 {port} 포트에서 시작되었습니다.")

while True:
    client_socket, addr = server_socket.accept()
    print(f"클라이언트가 연결되었습니다: {addr}")

    data = client_socket.recv(1024).decode('utf-8')
    response = control_led(data)

    print(f"수신된 데이터: {data}")
    print(f"응답 데이터: {response}")

    client_socket.send(response.encode('utf-8'))

    client_socket.close()


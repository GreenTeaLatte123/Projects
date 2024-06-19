import socket
import time
import os
from time import sleep
from servo import left, center, right
from dcmotor import go, back, stop
from gpiozero import LED, OutputDevice
from firebase_admin import credentials, storage, initialize_app, db

led_red = LED(17)
led_green = LED(27)

def control_led(command):
    if command.strip() == 'turnOn':  # 공백 제거 후 비교
        led_red.on()
        return 'LED 켜짐'
    elif command.strip() == 'turnOff':  # 공백 제거 후 비교
        led_red.off()
        return 'LED 꺼짐'
    elif command.strip() == 'LEFT':
        led_green.on()
        sleep(1)
        led_green.off()
        right()
        return '좌회전'
    elif command.strip() == 'CENTER':
        led_green.on()
        sleep(1)
        led_green.off()
        center()
        return '중립'
    elif command.strip() == 'RIGHT':
        led_green.on()
        sleep(1)
        led_green.off()
        left()
        return '우회전'
    elif command.strip() == 'GO':
        led_green.on()
        sleep(1)
        led_green.off()
        back()
        return '직진'
    elif command.strip() == 'BACK':
        led_green.on()
        sleep(1)
        led_green.off()
        go()
        return '후진'
    elif command.strip() == 'STOP':
        led_green.on()
        sleep(1)
        led_green.off()
        stop()
        return '정지'
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


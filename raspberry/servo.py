from gpiozero import Servo
from time import sleep

# Raspberry Pi의 GPIO 핀 번호
servo_pin = 21

# Servo 객체 생성
servo = Servo(servo_pin)

def left():
    servo.value = 1   
          
def center():
    servo.value = 0.5

def right():
    servo.value = -1


import serial
from dcmotor import loop1, loop2


port = '/dev/ttyUSB0'
SerialFromArduino = serial.Serial(port, 9600);
SerialFromArduino.flushInput()

while True:
    input_s = SerialFromArduino.readline()
    input_s = input_s.decode('utf-8').strip()
    print(input_s)
    if input_s == 'CDS on':  # 빛이 감지될 때
        loop1()
    elif input_s == 'CDS off':
        loop2()


import serial

port = '/dev/ttyUSB0'
SerialFromArduino = serial.Serial(port, 9600);

SerialFromArduino.flushInput()

while True:
    input_s = SerialFromArduino.readline()
    input_s = input_s.decode('utf-8').strip()
    print(input_s)
from gpiozero import OutputDevice
from time import sleep

stepPin = [2, 3, 4, 5]

stepPins = [OutputDevice(pin) for pin in stepPin]

def aStep(s):
    if s == 0:
        stepPins[0].off()
        stepPins[1].on()
        stepPins[2].on()
        
        stepPins[3].off()
    elif s == 1:
        stepPins[0].off()
        stepPins[1].on()
        stepPins[2].off()
        stepPins[3].on()
    elif s == 2:
        stepPins[0].on()
        stepPins[1].off()
        stepPins[2].off()
        stepPins[3].on()
    elif s == 3:
        stepPins[0].on()
        stepPins[1].off()
        stepPins[2].on()
        stepPins[3].off()

def doSteps(dir, nSteps, del_):
    for i in range(nSteps):
        aStep((nSteps-i-1) if dir else i % 4)
        sleep(del_ / 1000.0)

def setup():
    pass

def loop():
    while True:
        doSteps(False, 200, 5)
        sleep(1)
        doSteps(True, 200, 5)
        sleep(1)

if __name__ == '__main__':
    setup()
    try:
        loop()
    except KeyboardInterrupt:
        pass
    finally:
        for pin in stepPins:
            pin.close()

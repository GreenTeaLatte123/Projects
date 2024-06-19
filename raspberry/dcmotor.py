from gpiozero import OutputDevice
from time import sleep

stepPin = [19, 26, 16, 20]

def create_step_pins():
    return [OutputDevice(pin) for pin in stepPin]

def aStep(stepPins, s):
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

def bStep(stepPins, s):
    if s == 3:
        stepPins[0].off()
        stepPins[1].on()
        stepPins[2].on()
        stepPins[3].off()
    elif s == 2:
        stepPins[0].off()
        stepPins[1].on()
        stepPins[2].off()
        stepPins[3].on()
    elif s == 1:
        stepPins[0].on()
        stepPins[1].off()
        stepPins[2].off()
        stepPins[3].on()
    elif s == 0:
        stepPins[0].on()
        stepPins[1].off()
        stepPins[2].on()
        stepPins[3].off()

def doStep1(stepPins, dir, nSteps, del_):
    for i in range(nSteps):
        aStep(stepPins, (nSteps-i-1) if dir else i % 4)
        sleep(del_ / 1000.0)

def doStep2(stepPins, dir, nSteps, del_):
    for i in range(nSteps):
        bStep(stepPins, (nSteps-i-1) if dir else i % 4)
        sleep(del_ / 1000.0)

def setup():
    pass

def loop1():
    stepPins = create_step_pins()
    for _ in range(5):
        doStep1(stepPins, False, 280, 4)
        sleep(1)
    for pin in stepPins:
        pin.close()

def loop2():
    stepPins = create_step_pins()
    for _ in range(5):
        doStep2(stepPins, False, 280, 4)
        sleep(1)
    for pin in stepPins:
        pin.close()

if __name__ == '__main__':
    setup()
    while True:
        k = input('command = ')
        if k == 'yes':
            try:
                loop1()
            except KeyboardInterrupt:
                break
        elif k == 'no':
            try:
                loop2()
            except KeyboardInterrupt:
                break
        else:
            print("Invalid command. Please enter 'yes' or 'no'.")

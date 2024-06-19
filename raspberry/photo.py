from gpiozero import DigitalInputDevice
from signal import pause
from datetime import datetime

LIGHT = 4  # BCM. 8

# GPIO 핀 8번을 입력 장치로 설정합니다.
input_device = DigitalInputDevice(LIGHT)

def print_light_state():
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    if input_device.is_active:  # 빛이 감지될 때
        print(timestamp, "Light")
    else:  # 빛이 없을 때
        print(timestamp, "Dark")

# 이벤트 핸들러를 등록하여 입력 상태가 변경될 때마다 상태를 출력합니다.
input_device.when_activated = print_light_state
input_device.when_deactivated = print_light_state

print("Monitoring light levels... Press Ctrl+C to exit.")
pause()  # 프로그램이 종료될 때까지 대기합니다.

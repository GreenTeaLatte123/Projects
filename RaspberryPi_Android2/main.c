	#include "./main.h"

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <wiringPiI2C.h>

#define ROWS 4
#define COLS 4

// 키패드 매트릭스의 GPIO 핀 설정
int rowPins[ROWS] = { 16,13 ,12, 6 };
int colPins[COLS] = { 21, 26, 28, 29 };

// 키패드 버튼의 레이아웃 정의
char keypadLayout[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

void setupKeypad() {
  wiringPiSetup();

  // 행 핀을 출력으로 설정하고 LOW로 초기화
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  // 열 핀을 입력으로 설정하고 풀업 모드로 활성화
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT);
    pullUpDnControl(colPins[i], PUD_UP);
  }
}

char getKeyPressed() {
  char keyPressed = '\0';

  // 각 행을 스캔하면서 버튼 입력 체크
  for (int i = 0; i < ROWS; i++) {
    // 현재 행을 HIGH로 설정
    digitalWrite(rowPins[i], HIGH);

    // 모든 열을 검사하여 버튼 상태 확인
    for (int j = 0; j < COLS; j++) {
      if (digitalRead(colPins[j]) == LOW) {
        keyPressed = keypadLayout[i][j];
        break;
      }
    }

    // 현재 행을 다시 LOW로 설정
    digitalWrite(rowPins[i], LOW);

    // 버튼이 눌렸으면 루프 종료
    if (keyPressed != '\0') {
      break;
    }
  }

  return keyPressed;
}

int main(int args, char** argv) 
{
	  setupKeypad();

  while (1) {
    char key = getKeyPressed();
    if (key != '\0') {
      printf("Key Pressed: %c\n", key);
    }
  }
  
	getCommand getcmd = { 0, };
	sensors sensor = { 0, };
	connection(&getcmd);
	init_sensor();

	uint8_t led_change = 0x00;
	while (true) 
	{
		json_object* data = json_object_object_get(getcmd.rootObj, "data");
		// printf("%s", getcmd.command);

		sensor = json_parser(data);
		if (strcmps(sensor.led, "True") == 0) 
		{  
			led_change = ~led_change;            // led_change 값을 반전시킨다.
			led(led_change, getcmd);              // led_change 값을 이용하여 LED를 켜거나 끈다.
			led_change ? response("200", &getcmd) : response("LED OFF!", &getcmd);  // led_change 값에 따라 응답을 보낸다.
			led_change ? printf("LED ON!\n") : printf("LED OFF!\n");                    // led_change 값에 따라 콘솔에 출력한다.
		}

		if (strcmps(sensor.buzzer_usage, "True") == 0) 
		{  
			uint16_t HZ = (uint16_t)atoi(sensor.buzzer_hertz);  // buzzer_hertz 값을 정수형으로 변환하여 HZ에 저장한다.
			response("200", &getcmd);  
			printf("BUZZER ON! %d\n", HZ);  // 콘솔에 "BUZZER ON! HZ"를 출력한다.

			for (int i = 0; i < 3; i++) 
			{
				buzzer(HZ, getcmd);          // HZ 주파수로 부저를 울린다.
				delay(300);                  // 300ms 딜레이를 준다.
				HZ += 15;                    // HZ 값을 15 증가시킨다.
			}
			buzzer(0, getcmd);  // 부저를 끈다.
		}

		if (strcmps(sensor.motor_usage, "True") == 0)
		{
			printf("MotorMove! %d\n", atoi(sensor.motor_angle));  // 콘솔에 "MotorMove! motor_angle"를
											 // 출력한다.
			response("Motor Move!", &getcmd);  // "Motor Move!" 응답을 보낸다.
			for (int i = 0; i < atoi(sensor.motor_angle); i++) {
				motor(200, i);
			}  // motor_angle 값만큼 모터를 회전시킨다.
		}

		// LCD 한줄에 최대 16자
		if (strcmps(sensor.lcd_usage, "True") == 0) 
		{ 
			response(sensor.lcd_text, &getcmd);  // lcd_text 값을 응답으로 보낸다.
			if (strlen(sensor.lcd_text) > 16)  // 만약 lcd_text의 길이가 16보다 크면
			{  
				lcdLoc(LINE1);  // 첫 번째 줄에 커서를 위치시킨다.
				char* lcd_print1 = str_slicing( sensor.lcd_text, 0, 16);  // lcd_text의 0~15번째 문자열을 lcd_print1에 저장한다.
				typeln(lcd_print1);  // lcd_print1을 첫 번째 줄에 출력한다.

				char* lcd_print2 = str_slicing( sensor.lcd_text, 16, strlen(sensor.lcd_text) + 1);  // lcd_text의 16번째 이후 문자열을 lcd_print2에 저장한다.
				lcdLoc(LINE2);       // 두 번째 줄에 커서를 위치시킨다.
				typeln(lcd_print2);  // lcd_print2를 두 번째 줄에 출력한다.
				// delay(2000);
				// ClrLcd();

				// typeln("Int  ");
				// int value = 201904;
				// typeInt(value);

				// delay(2000);
				// lcdLoc(LINE2);
				// typeln("Float ");
				// float FloatVal = 10045.25989;
				// typeFloat(FloatVal);
				// delay(2000);
			}
		}
	}
	
}

void init_sensor() 
{
	if (wiringPiSetup() == -1) return -1;
	pinMode(LED_PIN, OUTPUT);    // LED_PIN을 출력으로 설정한다.
	softToneCreate(BUZZER_PIN);  // BUZZER_PIN을 소프트톤으로 설정한다.
	lcd_init();                  // LCD를 초기화한다.

	pinMode(MOTOR_PIN, OUTPUT);    // MOTOR_PIN을 출력으로 설정한다.
	digitalWrite(MOTOR_PIN, LOW);  // MOTOR_PIN을 LOW로 설정한다.

	pinMode(LIGHTSEN_OUT, INPUT);  // LIGHTSEN_OUT을 입력으로 설정한다.

	pinMode(SOUND_IN, INPUT);  // SOUND_IN을 입력으로 설정한다.

	pinMode(TRIG_PIN, OUTPUT);  // TRIG_PIN을 출력으로 설정한다.
	pinMode(ECHO_PIN, INPUT);   // ECHO_PIN을 입력으로 설정한다.
}

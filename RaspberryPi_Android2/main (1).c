#include "./main.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <wiringPiI2C.h>
#include <json-c/json.h>
#include "./data.h"
#include "./data.json"


#define ROWS 4
#define COLS 4

int rowPins[ROWS] = { 16, 13, 12, 6 };
int colPins[COLS] = { 21, 26, 28, 29 };

char keypadLayout[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { 'D', '0', 'E', 'F' }
};

void setupKeypad() {
  wiringPiSetup();

  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT);
    pullUpDnControl(colPins[i], PUD_UP);
  }
}

char getKeyPressed() {
  char keyPressed = '\0';

  for (int i = 0; i < ROWS; i++) {
    digitalWrite(rowPins[i], HIGH);
    delay(5); // 추가: 딜레이를 줌으로써 안정적인 버튼 입력 확인

    for (int j = 0; j < COLS; j++) {
      if (digitalRead(colPins[j]) == LOW) {
        keyPressed = keypadLayout[i][j];
        break;
      }
    }

    digitalWrite(rowPins[i], LOW);

    if (keyPressed != '\0') {
      break;
    }
  }

  return keyPressed;
}

void saveToJson(const char* filename, const char* key) {
  json_object* jsonObj = json_object_new_object();
  json_object_object_add(jsonObj, "key", json_object_new_string(key));

  const char* jsonString = json_object_to_json_string_ext(jsonObj, JSON_C_TO_STRING_PRETTY);
  FILE* file = fopen(filename, "w");
  if (file != NULL) {
    fputs(jsonString, file);
    fclose(file);
  }

  json_object_put(jsonObj);
}

void saveToHeader(const char* filename, const char* key) {
  FILE* file = fopen(filename, "w");
  if (file != NULL) {
    fprintf(file, "#ifndef DATA_H\n");
    fprintf(file, "#define DATA_H\n\n");
    fprintf(file, "const char* key = \"%s\";\n\n", key);
    fprintf(file, "#endif\n");
    fclose(file);
  }
}

int main(int args, char** argv) {
  setupKeypad();

  while (1) {
    char key = getKeyPressed();
    if (key != '\0') {
      printf("Key Pressed: %c\n", key);
      saveToJson("data.json", &key);
      saveToHeader("data.h", &key);
      delay(300); // 추가: 버튼 입력 후 일정 시간 동안 재입력을 방지하기 위한 딜레이
    }
  }

  return 0;
}

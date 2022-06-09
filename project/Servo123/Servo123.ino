#include <Servo.h>

Servo myservo;  // 서보 컨트롤 설정
// twelve servo objects can be created on most boards

int delayTime = 1000 * 60 * 60 * 2; // 2시간에 한번씩
// int delayTime = 1000 * 5; // 5초에 한번씩(테스트)

int pos = 0;    // variable to store the servo position

int servoMin = 0;

int servoMax = 180;

void setup() {
  myservo.attach(2);  // 2번핀에 모터핀 설정
}

void moveSlowly(int from, int to, Servo servo) {
  int increment = 5;
  int current = from;
  if (from > to) { 
    increment = -5;
  }
  while (current != to) {
    current = current + increment;
    servo.write(current);
    delay(50);
  }
}

void loop() {
  moveSlowly(servoMax, servoMin, myservo);
  delay(delayTime); // wait delayTime
  moveSlowly(servoMin, servoMax, myservo);
  delay(delayTime); // wait delayTime
}

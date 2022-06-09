#include <DHT.h>    //DHT.h 라이브러리 선언
#define DHTPIN 2    //DHT핀을 2번으로 선언
#define DHTTYPE DHT22   //DHT타입을 DHT22로 선언
DHT dht(DHTPIN, DHTTYPE);   //DHT설정을 2번핀과 dht22로 선언

int t = 0;    //온도변수 선언
int h = 0;    //습도변수 선언
int r = 3;    //변수 선언
  
void setup() {
  Serial.begin(9600);   //시리얼 통신속도를 9600으로 선언
  dht.begin();
  pinMode(r, OUTPUT);   //r = 3번핀 모드를 OUTPUT모드로 선언
}

void dht22() {    //함수 dht22
  t = dht.readTemperature();    //변수 t에 온도 값을 저장
  h = dht.readHumidity();   //변수 h에 습도 값을 저장
  
  Serial.print("Temperature : ");
  Serial.print(t);    //온도값 출력
  Serial.println("C");    //문자열 출력
  Serial.print("Humidity : ");    //문자열 출력
  Serial.print(h);    //습도값 출력
  Serial.println("%");    //문자열 출력
}

void loop() {
  dht22();    //함수 dht22실행

  if(t >= 37.8 or h >= 55)   //조건문 선언 온도의 값이 25이상일 경우
  {
    digitalWrite(r, HIGH);    //r의 출력을 HIGH
  }
  else    //조건문 t의 값이 25이상이 아닐경우
  {
    digitalWrite(r, LOW);   //r의 출력을 LOW
  }
  
  delay(2000);    //루프딜레이 2초
}

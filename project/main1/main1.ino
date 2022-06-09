#include <DHT.h>    //DHT.h 라이브러리 선언
#define DHTPIN 2    //DHT핀을 2번으로 선언
#define DHTTYPE DHT22   //DHT타입을 DHT22로 선언
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
DHT dht(DHTPIN, DHTTYPE);   //DHT설정을 2번핀과 dht22로 선언 
LiquidCrystal_I2C lcd(0x27,16,2); // LCD주소: 0x27 또는 0x3F
#include <SPI.h>
#include <Ethernet.h>


byte mac[] ={0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
IPAddress ip(222,105,251,71);
EthernetServer server(80);
int t = 0;    //온도변수 선언
int h = 0;    //습도변수 선언
int r = 3;    //변수 선언
  
void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);   //시리얼 통신속도를 9600으로 선언
  
  dht.begin();
  delay(2000);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  delay(5000);
  lcd.clear();
  pinMode(r, OUTPUT);   //r = 3번핀 모드를 OUTPUT모드로 선언
}

void dht22() {    //함수 dht22
  t = dht.readTemperature();    //변수 t에 온도 값을 저장
  h = dht.readHumidity();   //변수 h에 습도 값을 저장
}

void loop() {

  web();
  lcd_loop();
  

}
void lcd_loop(){
  dht22();    //함수 dht22실행
  lcd.setCursor(0,0); // LCD Cursor 원점
  lcd.print("Temp:"); // LCD에 "temp" 표시
  lcd.print(t,1); // 온도값 LCD로 출력
  lcd.print(" C "); // 온도 단위 표시
  lcd.setCursor(0,1); //LCD 커서 줄바꿈
  lcd.print("Humidity:"); //LCD 2번째 줄에 "humidity:" 출력
  lcd.print(h); //습도값 LCD에 출력
  lcd.print(" % "); //습도 단위 출력
  lcd.println("  ");

  if(t >= 37.8 or h >= 55)   //조건문 선언 온도의 값이 25이상일 경우
  {
    digitalWrite(r, HIGH);    //r의 출력을 HIGH
    lcd.setCursor(11,0);
    lcd.print("Open ");
  }
  else    //조건문 t의 값이 25이상이 아닐경우
  {
    digitalWrite(r, LOW);   //r의 출력을 LOW
    lcd.setCursor(11,0);
    lcd.print("Close");
  }
  
  delay(2000);    //루프딜레이 2초

}
void web(){
  EthernetClient client = server.available();

  if(client){
    boolean currentLineIsBlank = true;
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        if(c == '\n' && currentLineIsBlank){
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
//                    HTML start
          client.println("<!DOCTYPE html>");
          client.println("<html lang=\"en\">");
          client.println("<head>");
          client.println("<meta charset=\"utf-8\" />");
          client.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
//                    Title
          client.println("<title>Egg Incubator</title>");
          client.println("<style>");
          client.println("body{overflow:hidden;}");
          client.println("</style>");
          
          client.println("</head>");          
//                    Body
          client.println("<body>");
          client.println("<h1> 계란 부화기 </h1>");
          client.println("<p>온도 : ");
          dht22();
          client.println(t);
          client.println("℃</p>");
          client.println("<br>");
          client.println("<p>습도 : ");
          client.println(h);
          client.println("%</p>");        

          client.println("</body>");
          client.println("</html>");
//        End
          client.stop();

          
          
        }
      }
    }
}
}

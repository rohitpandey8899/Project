#include <Wire.h>
#include<NewPing.h>
#include <Adafruit_MLX90614.h>
#include<AFMotor.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     4 
Adafruit_SSD1306 display(OLED_RESET);


#define eco_pin 6
#define trg_pin 5
#define max_dis 1000

NewPing sonar(trg_pin, eco_pin, max_dis);
int dis =0;
int temp =0;
AF_DCMotor m1(1,MOTOR12_64KHZ);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin(); 
       m1.setSpeed(255);
       display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  led("WELCOME",2,22,7);
  led("in my office",1,25,22);
       
}
void loop() {
led("WELCOME",2,22,7);
  led("come closer to 5-2cm",1,7,22);
  display.clearDisplay();
dis = sonar.ping_cm();
Serial.println("Distance");
Serial.println(dis);
if(dis>0&&dis<5){
//  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
//  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
//  Serial.print("Ambientvvv = "); Serial.print(mlx.readAmbientTempF()); 
//  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
//  Serial.println();
delay(1500);
  temp = mlx.readObjectTempF();
//  Serial.println("Normal temp  ");
//  Serial.println(temp);
  if(temp<=99&&temp>=87){
     led("Teperature",1,12,7);
      display.setTextSize(2);
      display.setCursor(92,15);
display.setTextColor(WHITE);
display.println(temp);
display.display();
    Serial.println("Normal temp");
    delay(500);
    m1.run(FORWARD);
       delay(15000);
       m1.run(RELEASE);
       delay(500);
    }else{
      display.clearDisplay();
      led("Teperature",1,12,7);
      display.setTextSize(2);
      display.setCursor(92,15);
display.setTextColor(WHITE);
display.println(temp);
display.display();
display.clearDisplay();
      }
  delay(2000);
}
}

void led(String name,int size,int x,int y){
  display.setTextSize(size);
display.setTextColor(WHITE);
display.setCursor(x,y);
display.println(name);
display.display();
  }

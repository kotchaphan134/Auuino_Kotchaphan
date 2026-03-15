#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;

int lightVal;
int angle;
int percent;

void setup() {
  myServo.attach(9);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Smart Blinds");
  delay(2000);
  lcd.clear();
}

void loop() {
  lightVal = analogRead(A0);
  angle = map(lightVal, 0, 800, 180, 0);
  myServo.write(angle);
  percent = map(angle, 0, 180, 100, 0);
  lcd.setCursor(0, 0);
  lcd.print("Sun: ");
  lcd.print(lightVal);
  lcd.print("   "); 
  lcd.setCursor(0, 1);
  lcd.print("Open: ");
  lcd.print(percent);
  lcd.print("%   "); 
 
  delay(200);
}

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ประกาศอุปกรณ์
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;

// ประกาศตัวแปร
int lightVal;
int angle;
int percent;

void setup() {
  // ตั้งค่ามอเตอร์ที่ขา 9
  myServo.attach(9);
  
  // ตั้งค่าเริ่มต้นจอ LCD
  lcd.init();
  lcd.backlight();
  
  // โชว์ข้อความต้อนรับ
  lcd.setCursor(0, 0);
  lcd.print("Smart Blinds");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. อ่านค่าแสงจากขา A0
  lightVal = analogRead(A0);

  // 2. แปลงค่าแสงเป็นองศามอเตอร์ (แสง 0=เปิด180, แสง800=ปิด0)
  angle = map(lightVal, 0, 800, 180, 0);
  
  // สั่งมอเตอร์หมุนไปที่องศานั้น
  myServo.write(angle);

  // 3. แปลงองศามอเตอร์ให้เป็นเปอร์เซ็นต์ (0-100%)
  percent = map(angle, 0, 180, 100, 0);

  // 4. แสดงผลบรรทัดบน (ค่าแสง)
  lcd.setCursor(0, 0);
  lcd.print("Sun: ");
  lcd.print(lightVal);
  lcd.print("   "); // เคาะสเปซบาร์ลบเลขเก่า

  // 5. แสดงผลบรรทัดล่าง (เปอร์เซ็นต์การเปิดม่าน)
  lcd.setCursor(0, 1);
  lcd.print("Open: ");
  lcd.print(percent);
  lcd.print("%   "); // เคาะสเปซบาร์ลบเลขเก่า

  // 6. หน่วงเวลาไม่ให้จอทำงานหนักไป
  delay(200);
}

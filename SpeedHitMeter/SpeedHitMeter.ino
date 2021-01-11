#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const long interval = 1; // the time we need to wait
unsigned long lastMillis, previousMillis = 0; // millis() returns an unsigned long.
int waktu;
float jarak = 0.15; // 15cm to m.
int kunci, kunci_a = 0;
double speed;
const int frontSensor = 12;
const int backSensor = 11;
const int buzz = 4;
int percent;
String kata;
void setup()
{
  lcd.init();
  Serial.begin(9600);
  pinMode(frontSensor, INPUT);
  pinMode(backSensor, INPUT);
  pinMode(buzz, OUTPUT);
  lcd.backlight();
}

void loop() {
  int a = digitalRead(frontSensor);
  int b = digitalRead(backSensor);
  unsigned long currentMillis = millis(); // grab current time
  digitalWrite(buzz, LOW);
  if (a == 1 && b == 0 && kunci == 0) {
    if (currentMillis - previousMillis >= interval) {
      lastMillis = currentMillis;
      kunci = 1;
    }
  }
  if (kunci == 1) {
    if (a == 1 && b == 1 && kunci_a == 0) {
      digitalWrite(buzz, HIGH);
      previousMillis = millis();
      kunci_a = 1;
    }
    if (kunci_a == 1) {
      waktu = (previousMillis - lastMillis) + 1;
      speed = jarak / waktu * 1000;
      percent = mapFloat(speed, 0, 6, 0, 100);
      lcd.setCursor(0, 0); lcd.print(speed, 3); lcd.print("  ");
      lcd.setCursor(6, 0); lcd.print("m/s");
      lcd.setCursor(0, 1); lcd.print(percent); lcd.print("  ");
      lcd.setCursor(3, 1); lcd.print("%");
      delay(100);
    }
    if (!a && !b) {
      kunci_a = 0;
      kunci = 0;
    }
  }
  //  lcd.setCursor(0, 0); lcd.print("Speed= ");
  //  Serial.print(lastMillis);
  //  Serial.print(" | ");
  //  Serial.print(previousMillis);
  //  Serial.print(" | ");
  //  Serial.println(speed);
}

int mapFloat(float x, float in_min, float in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

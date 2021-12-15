#include <LiquidCrystal.h>
#include <RTClib.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define ALARM_SETED_LED 12
#define BUZZER 8

DS1302 rtc(9, 10, 11);

char buf[20];

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(ALARM_SETED_LED, OUTPUT);
  
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  lcd.begin(16, 2);
  digitalWrite(ALARM_SETED_LED, HIGH);
}

void loop() {
  DateTime now = rtc.now();

  Serial.println(now.tostr(buf));

  lcd.setCursor(0, 0);
  lcd.print(String(now.tostr(buf)).substring(0, 11));
  lcd.setCursor(0, 1);
  lcd.print(String(now.tostr(buf)).substring(11));

  // Subscribe to alarm_seted event
  // To declare datetime alarm and message

  if (strcmp(now.tostr(buf), "2021/12/15 12:21:00") == 0) {
    // TODO: Publish alarm_triggered event
    
    lcd.setCursor(0, 1);
    lcd.print(String("Wake Up "));
    
    tone(BUZZER, 440.00, 500);
    delay(600);
    lcd.display();
    tone(BUZZER, 440.00, 500);
    delay(600);
    lcd.noDisplay();
    tone(BUZZER, 440.00, 550);
    delay(600);
    lcd.display();
  
    tone(BUZZER, 349.23, 400);
    delay(450);
    lcd.noDisplay();
    tone(BUZZER, 523.25, 300);
    delay(325);
    lcd.display();
    tone(BUZZER, 440.00, 600);
    delay(600);
    lcd.noDisplay();
    
    tone(BUZZER, 349.23, 400);
    delay(450);
    lcd.display();
    tone(BUZZER, 523.25, 300);
    delay(325);
    lcd.noDisplay();
    tone(BUZZER, 440.00, 600);
    delay(600);
    lcd.display();

    lcd.clear();
    digitalWrite(ALARM_SETED_LED, LOW);
  }

  delay(1000);
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define GAS_SENSOR 34
#define LED 2
#define BUZZER 25

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Welcome Screen
  display.setTextSize(2);
  display.setCursor(10, 15);
  display.println("GAS");
  display.setCursor(10, 40);
  display.println("MONITOR");
  display.display();

  delay(2000);
}

void loop() {

  int gas = analogRead(GAS_SENSOR);

  Serial.print("Gas Value: ");
  Serial.println(gas);

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Gas Leakage Monitor");

  // Gas Value
  display.setCursor(0,15);
  display.print("Gas Value: ");
  display.print(gas);

  if(gas > 2000){

    digitalWrite(LED,HIGH);
    digitalWrite(BUZZER,HIGH);

    display.setTextSize(2);
    display.setCursor(0,35);
    display.println("ALERT!");

    display.setTextSize(1);
    display.setCursor(0,56);
    display.print("Gas Leak Detected");

  }
  else{

    digitalWrite(LED,LOW);
    digitalWrite(BUZZER,LOW);

    display.setTextSize(2);
    display.setCursor(20,38);
    display.println("SAFE");

  }

  display.display();

  delay(500);
}
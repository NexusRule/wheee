SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include "oled-wing-adafruit.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include <Wire.h>
VCNL4040 proximitySensor;
OledWingAdafruit display;

bool dio = 0;
bool giorno = 0;
bool giovana = 0;
int jotaro = 0;
int joseph = 0;
int jonothan = 0;
String shoyo = "A";

#define pot A0
#define therm A1
#define but D2
#define hiLite D3
#define gLite D4
#define lowLite D5

void lightPara()
{

  Serial.print(shoyo);

  jonothan = proximitySensor.getAmbient();

  bool butt = digitalRead(but);
  if (butt == 0)
  {
    if (dio == 0)
    {
      dio = 1;
    }
    else if (dio == 1)
    {
      dio = 0;
    }
    delay(500);
  }

  if (jonothan <= joseph)
  {
    digitalWrite(lowLite, HIGH);
    digitalWrite(gLite, LOW);
    digitalWrite(hiLite, LOW);
    Serial.write("low");
    delay(200);
  }
  else if (jonothan > jotaro)
  {
    digitalWrite(lowLite, LOW);
    digitalWrite(gLite, LOW);
    digitalWrite(hiLite, HIGH);
    Serial.write("high");
    delay(200);
  }
  else
  {
    digitalWrite(lowLite, LOW);
    digitalWrite(gLite, HIGH);
    digitalWrite(hiLite, LOW);
    Serial.write("good");
    delay(200);
  }

  if (dio == 0)
  {
    jotaro = analogRead(pot);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("max - ");
    display.println(jotaro);
    display.print("min - ");
    display.println(joseph);
    display.display();

    if (joseph >= jotaro)
    {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("error: min is greater than max!");
      display.display();
    }

    delay(100);
  }
  else if (dio == 1)
  {
    joseph = analogRead(pot);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print("min - ");
    display.println(joseph);
    display.print("max - ");
    display.println(jotaro);
    display.display();

    if (joseph >= jotaro)
    {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("error: min is greater than max!");
      display.display();
    }
    shoyo = "A";
    delay(100);
  }

  display.print("light lvl - ");
  display.print(jonothan);
  display.display();
}

void temp()
{
  uint64_t reading = analogRead(therm);

  double voltage = (reading * 3.3) / 4095.0;
  double temperature = (voltage - 0.5) * 100;

  double f2 = (reading * 3.3) / 4095.0;
  double f1 = (f2 - 0.5) * 100;
  double f = (f1 * 1.8) + 32;

  display.clearDisplay();
  display.setCursor(15, 15);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(temperature);
  display.print("C  |  ");
  display.print(f);
  display.print("F");
  display.display();
  shoyo = "B";
  delay(100);
}

void setup()
{
  Serial.begin(9600);

  display.setup();
  display.clearDisplay();
  display.display();

  Wire.begin();

  proximitySensor.begin();
  proximitySensor.powerOffProximity();
  proximitySensor.powerOnAmbient();

  if (proximitySensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
    while (1)
      ;
  }

  pinMode(pot, INPUT);
  pinMode(but, INPUT);
  pinMode(therm, INPUT);
  pinMode(lowLite, OUTPUT);
  pinMode(gLite, OUTPUT);
  pinMode(hiLite, OUTPUT);
}

void loop()
{
  display.loop();

  if (display.pressedA())
  {
    shoyo = "A";
  }
  else if (display.pressedC())
  {
    shoyo = "B";
  }

  if (shoyo == "A")
  {
    lightPara();
    Serial.print(shoyo);
  }
  else if (shoyo == "B")
  {
    temp();
    Serial.print(shoyo);
  }
  Serial.print(shoyo);
}

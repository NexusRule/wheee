/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/fxxsj/OneDrive/Desktop/wheee/src/wheee.ino"
void lightPara();
void temp();
void setup();
void loop();
#line 1 "c:/Users/fxxsj/OneDrive/Desktop/wheee/src/wheee.ino"
SYSTEM_THREAD(ENABLED);
#include "oled-wing-adafruit.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include <blynk.h>
VCNL4040 proximitySensor;
OledWingAdafruit display;

bool dio = 0;
bool giorno = 0;
bool giovana = 0;
bool grange = 0;
int jotaro = 0;
int joseph = 0;
int jonothan = 0;
String shoyo = "A";
String yama = "good";

#define pot A0
#define therm A1
#define but D7
#define hiLite A4
#define gLite A3
#define lowLite A2

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
    Blynk.notify("yo the lights too dim");
    yama = "low";
    delay(200);
  }
  else if (jonothan > jotaro)
  {
    digitalWrite(lowLite, LOW);
    digitalWrite(gLite, LOW);
    digitalWrite(hiLite, HIGH);
    Serial.write("high");
    Blynk.notify("yo the lights too bright");
    yama = "high";
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
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, f);
  delay(100);
}

void setup()
{
  Serial.begin(9600);

  display.setup();
  display.clearDisplay();
  display.display();

  Blynk.begin("3ooCt2NcBosv3c9DV-MGSexZ0aBKUMTc", IPAddress(167, 172, 234, 162), 8080);

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
  Blynk.run();

  grange = digitalRead(V0);

  if (display.pressedA())
  {
    if (shoyo == "A")
    {
      shoyo = "B";
    }
    else if (shoyo == "B")
    {
      shoyo = "A";
    }
    delay(500);
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
  else if (grange == 1)
  {
    Series.print("tootally secret easter egg");
  }
}
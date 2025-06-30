#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include <Servo.h>

#define FONA_RX            11
#define FONA_TX            10
#define FONA_RST           4

#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

char PHONE_1[21] = "+917815981481"; // Enter your First Number here.
char PHONE_2[21] = "+919492024089";
char gasalert[141] = "Gas Leakage Detected location-- https://maps.app.goo.gl/yMoMVtFcwRjUmwLm6";
int gas_sensor_pin = A0;
Servo myservo;
int servoPin = 9; // Servo control pin
int servoAngle = 0; // Initial angle for the servo

void setup()
{
  pinMode(gas_sensor_pin, INPUT);
  myservo.attach(servoPin); // Attaching the servo to its pin
  Serial.begin(115200);
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(9600); // if you're using software serial
  if (!fona.begin(fonaSS))
  { // can also try fona.begin(Serial1)
    Serial.println(F("Couldn't find FONA"));
    while (1)
      ;
  }

  fona.print("AT+CSMP=17,167,0,0\r");
  Serial.println(F("FONA is OK"));
  pinMode(gas_sensor_pin, INPUT);
{

  int gas_value = analogRead(gas_sensor_pin);
  Serial.print("GasValue:");
  Serial.println(gas_value);
  if (gas_value > 530 || gas_value > 250)
  {
    //tone(buzzer_pin,1000);
    Serial.println("Gas Leakage Detected ");

    // fire_flag = 0;

    make_multi_call();
    send_multi_sms();
    rotateServo(); // Rotate the servo when gas is detected
    exit;
  }
}

void send_multi_sms()
{
  if (PHONE_1 != "")
  {
    Serial.print("Phone 1: ");
    fona.sendSMS(PHONE_1, gasalert);
    Serial.print("Phone 2: ");
    fona.sendSMS(PHONE_2, gasalert);

    delay(1000);
  }
}

void make_multi_call()
{
  if (PHONE_1 != "")
  {
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
    Serial.print("Phone 2: ");

    make_call(PHONE_2);
    delay(1000);
  }
}

void make_call(String phone)
{
  Serial.println("calling....");
  fona.println("ATD" + phone + ";");
  delay(20000); //20 sec delay
  fona.println("ATH");
  delay(1000); //1 sec delay
}

void rotateServo()
{
  for (servoAngle = 0; servoAngle <= 180; servoAngle += 10)
  {
    myservo.write(servoAngle);
    delay(50);
  }
  delay(1000); // Hold at the rotated position for 1 second
  for (servoAngle = 180; servoAngle >= 0; servoAngle -= 10)
  {
    myservo.write(servoAngle);
    delay(50);
    }
}

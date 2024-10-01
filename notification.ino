#define BLYNK_TEMPLATE_ID "TMPL3QsWq-XW2"
#define BLYNK_TEMPLATE_NAME "breast cancer"
#define BLYNK_AUTH_TOKEN "EqSHDGhIJVyQ5PxV5T2TjdkswJvNc4k4"

#include<WiFi.h>
#include<BlynkSimpleEsp32.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Pin assignments
#define ONE_WIRE_BUS 15  // DS18B20 pin
#define TOUCH_PIN 23      // Touch sensor pin
#define FORCE_PIN 34     // Analog pin for force sensor

// Setup OneWire instance and DallasTemperature library
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char ssid[] = "vivo Y33s";
char password[] = "sodhi...";
BlynkTimer timer;

void sendsensordata(){
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0); // Get temperature in Celsius

  // Read force sensor value
  int forceValue = analogRead(FORCE_PIN);

  // Read touch sensor value (1 if touched, 0 otherwise)
  int touchValue = digitalRead(TOUCH_PIN);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(",Force: ");
  Serial.print(forceValue);
  Serial.print(",Touch: ");
  Serial.println(touchValue);
  Blynk.virtualWrite(V2,temperature);
  Blynk.virtualWrite(V3,forceValue);
  Blynk.virtualWrite(V4,touchValue);
  if(temperature > 32 && forceValue <= 600 && touchValue == 0){
    Blynk.logEvent("breast_alert","positive");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(TOUCH_PIN,INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);
  timer.setInterval(1000,sendsensordata);

}

void loop() {
  Blynk.run();
  timer.run();
}

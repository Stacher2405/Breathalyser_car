#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "page.h"

const char* ssid = "";
const char* password = "";

const int alk_sensor_pin = 34;
WebServer server(80);

const int base_value = 1; //offset - to be calibrate
const int max_value = 4095;

void left(int power) {
  digitalWrite(26, power > 0);
  digitalWrite(27, power < 0);
  analogWrite(25, abs(power));
}

void right(int power) {
  digitalWrite(33, power > 0);
  digitalWrite(32, power < 0);
  analogWrite(4, abs(power));
}

void measure() {
  int alk_sensor_value = analogRead(alk_sensor_pin);

  Serial.println(alk_sensor_value);

  float ppm = (float)(alk_sensor_value - base_value)*(500.0 / (max_value - base_value));

  float promil = ppm*0.004;
  
  server.send(200, "text/html", String(promil, 2));
}

void setup(){

  Serial.begin(115200);

  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  
  Serial.print("Wi-fi connecting");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Your ESP IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
    server.send(200, "text/html", html);
  });
  server.on("/measure", measure);

  server.on("/move", [] (){
    left(server.arg("l").toInt());
    right(server.arg("r").toInt());
  });
  server.begin();
}
void loop() {
  server.handleClient();
  delay(2);
}
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wi-fi password";
const char* password = "password";

const int alk_sensor_pin = 34;
WebServer server(80);

const int base_value = 300; //offset - to be calibrate
const int max_value = 4095;

void measure() {
  int alk_sensor_value = analogRead(alk_sensor_pin);

  Serial.println(alk_sensor_value);

  float ppm = (float)(alk_sensor_value - base_value)*(500.0 / (max_value - base_value));

  float promil = ppm*0.004;

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='1'>";
  html += "<title> etanol sensor test </title>";
  html += "</head><body>";
  html += "<h1>Alkohol measurement</h1>";
  html += "<p>Value:</p>";
  html += "<h2>" + String(promil,2) + "‰</h2>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup(){

  Serial.begin(115200);
  Serial.print("Wi-fi connecting");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Your ESP IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", measure);
  server.begin();
}
void loop() {
  server.handleClient();
  delay(2);
}

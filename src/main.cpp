#include <Arduino.h>
#include <ESP32Servo.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "PKC Security";
const char* password = "dam2ranch2comet2gist2slay2kept";
bool complete = true;

Servo servo;
// WiFiServer server{80, 1};
HTTPClient http;

int pos = 360;
const int servoPin = 18;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

  // Set up mDNS responder
	// if(!MDNS.begin("timey"))
	// {
	// 	Serial.println("Error setting up MDNS responder!");
	// 	while(true)
	// 	{
	// 		delay(1000);
	// 	}
	// }
	// Serial.println("mDNS responder started");

  // // Start TCP server
  // server.begin();
  // Serial.println("TCP server started");

  // // Add service to MDNS-SD
	// MDNS.addService("http", "tcp", 80);

  // Configure servo motor
  servo.setPeriodHertz(50);
  servo.attach(servoPin, 1000, 2000);
}

void loop() {
  // Check if a client has connected
	// WiFiClient client = server.available();

  // Read the first line of HTTP request
	// NOTE: potential DDoS point
	// replace with timed and buffered read so only
	// GET / HTTP/1.1 is a valid request that fits
	// in the buffer
	// String req = client.readStringUntil('\r');

	// // Extract path part of HTTP GET request
	// int pathStartIndex = req.indexOf(' ');
	// int pathEndIndex = req.indexOf(' ', pathStartIndex + 1);

	// if(pathStartIndex == -1 || pathEndIndex == -1)
	// {
	// 	Serial.print("Invalid Request: ");
	// 	// NOTE: potential DDoS point as large requests could
	// 	// spam serial output and lock up the CPU
	// 	Serial.println(req);
	// 	return;
	// }

	// req = req.substring(pathStartIndex + 1, pathEndIndex);
	// Serial.print("Request: ");
	// // NOTE: potential DDoS point as large requests could
	// // spam serial output and lock up the CPU
	// Serial.println(req);

	// String resp;

	// if (req == "/") {
	// 	resp = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Zapping...</html>\r\n\r\n";
	// 	Serial.println("Zapping...");
	// 	Serial.println("Sending 200");
	// }
	// else {
	// 	resp = "HTTP/1.1 404 Not Found\r\n\r\n";
	// 	Serial.println("Sending 404");
	// } 

  servo.write(pos);
  pos -= 6;
  delay(1000);

  if (pos == 0) {
    http.begin("http://10.59.1.131/"); //Specify destination for HTTP request
    int httpResponse = http.GET();
    Serial.println(httpResponse);
    pos = 360;
  }
  
}
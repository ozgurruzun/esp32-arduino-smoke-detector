/*
  =====================================================
  Smoke Detection Module - ESP32 Communication Unit
  -----------------------------------------------------
  Receives digital alert from Arduino.
  Connects to WiFi.
  Sends SMS notification using Twilio REST API.
  =====================================================
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

// -------------------- Pin Definition --------------------
const uint8_t ARDUINO_SIGNAL_PIN = 15;

// -------------------- System Variables --------------------
bool messageSent = false;
int messageCounter = 1;

const String BASE_MESSAGE =
  "Smoke detected! Please take immediate action. Alert ID: ";

// =============================================================

void connectToWiFi();
void sendSMS();
void checkWiFiConnection();

// =============================================================

void setup() {
  Serial.begin(115200);
  pinMode(ARDUINO_SIGNAL_PIN, INPUT);

  connectToWiFi();
}

// =============================================================

void loop() {

  checkWiFiConnection();

  int signalState = digitalRead(ARDUINO_SIGNAL_PIN);

  if (signalState == HIGH && !messageSent) {
    Serial.println("⚠ Smoke detected. Sending SMS alert...");
    sendSMS();
    messageSent = true;
  }

  if (signalState == LOW) {
    messageSent = false;
  }

  delay(500);
}

// =============================================================
// Function: connectToWiFi
// Description: Connects ESP32 to WiFi network
// =============================================================
void connectToWiFi() {

  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// =============================================================
// Function: checkWiFiConnection
// Description: Reconnects if WiFi drops
// =============================================================
void checkWiFiConnection() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    connectToWiFi();
  }
}

// =============================================================
// Function: sendSMS
// Description: Sends SMS via Twilio REST API
// =============================================================
void sendSMS() {

  HTTPClient http;

  String message = BASE_MESSAGE + String(messageCounter++);
  String url =
    "https://api.twilio.com/2010-04-01/Accounts/" +
    String(TWILIO_ACCOUNT_SID) + "/Messages.json";

  http.begin(url);
  http.setAuthorization(TWILIO_ACCOUNT_SID, TWILIO_AUTH_TOKEN);
  http.addHeader("Content-Type",
                 "application/x-www-form-urlencoded");

  String postData =
    "To=" + String(TWILIO_TO_NUMBER) +
    "&From=" + String(TWILIO_FROM_NUMBER) +
    "&Body=" + message;

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.println("✅ SMS sent successfully!");
  } else {
    Serial.print("❌ SMS failed. Error: ");
    Serial.println(http.errorToString(httpResponseCode));
  }

  http.end();
}

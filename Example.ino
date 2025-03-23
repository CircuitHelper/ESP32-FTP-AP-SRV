#include <WiFi.h>
#include "ESP32FtpServer.h"

const char* apSSID     = "My_ESP32_AP";    // Change to your preferred SSID
const char* apPassword = "password123";      // Change to your preferred password

FtpServer ftpSrv;

// SD card chip select pin
#define SD_CS 5

void setup(void) {
  Serial.begin(115200);

  // Set up the ESP32 as an Access Point
  WiFi.softAP(apSSID, apPassword);
  Serial.println("Access Point started");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  pinMode(19, INPUT_PULLUP);

  // Initialize the SD card before starting the FTP server
  if (SD.begin(SD_CS)) {
    Serial.println("SD opened!");
    // Start the FTP server with username and password ("esp32", "esp32")
    ftpSrv.begin("esp32", "esp32");
  } else {
    Serial.println("SD open failed!");
  }
}

void loop(void) {
  ftpSrv.handleFTP();
}

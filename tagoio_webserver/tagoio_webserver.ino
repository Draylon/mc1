

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "redmi";
const char* password = "123987abc";

// Create an instance of the WebServer class
WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello, World!");
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

  // Define HTTP route handling
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "redmi";
const char* password = "123987abc";

const char* mqtt_server = "mqtt.tago.io";
const int mqtt_port = 1883;
const char* mqtt_user = "Token";
const char* mqtt_password = "d492e6a0-f4f5-4f92-8b5c-9d7f7a5ed1f5";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (client.connect("esp32_cli1", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
int init1=0;
uint32_t timestamp=0;
void loop() {
  if (!client.connected()) {
    reconnect();
  }

  if(init1==0){
    client.publish("init", "init1");
    client.subscribe("topico_35863");
    client.subscribe("1234");
    init1++;
  }

  client.loop();

  if(millis() - timestamp > 10000){
      Serial.println("publish?");
      client.publish("topico_79384","value_?");
      timestamp=millis();
  }

  delay(100);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("esp32_cli1", mqtt_user, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
      // Subscribe to topics here if needed
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
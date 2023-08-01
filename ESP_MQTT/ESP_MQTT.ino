

#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "nepaldigisys";
const char pass[] = "NDS_0ffice";

WiFiClient net;
MQTTClient MQTT_client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!MQTT_client.connect("arduino", "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nMQTT connected!");

  MQTT_client.subscribe("iot/test/topic_2");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  MQTT_client.begin("broker.emqx.io", net);
  MQTT_client.onMessage(messageReceived);

  connect();
}

void loop() {
  MQTT_client.loop();
  delay(10); 

  if (!MQTT_client.connected()) {
    connect();
  }

  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    MQTT_client.publish("iot/test/topic_1", "world");
  }
}

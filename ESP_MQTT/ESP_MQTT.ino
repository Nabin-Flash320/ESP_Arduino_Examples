
#include "ArduinoMqttClient.h"
#include <WiFiClientSecure.h>

const char *SSID = "nepaldigisys";
const char *PSWD = "NDS_0ffice";
const char *broker = "broker.emqx.io";
const uint16_t port = 1883;
const char *topic = "nds/test";

WiFiClientSecure wifi;
MqttClient mqttclient(wifi);

void connect_to_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PSWD);
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(".");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("Got IP ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  connect_to_wifi();
  while(!mqttclient.connect(broker, port))
  {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttclient.connectError());
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(".");
  delay(2000);
}

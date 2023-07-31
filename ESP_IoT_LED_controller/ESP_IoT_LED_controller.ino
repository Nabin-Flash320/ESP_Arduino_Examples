
#include <ArduinoWebsockets.h>
#include <Arduino_JSON.h>

#define LED_PIN LED_BUILTIN

const char* ssid = "nepaldigisys";
const char* wifipassword = "NDS_0ffice";
const char* server_host_address = "192.168.1.66";
const uint16_t server_port = 8080;

String led_onoff = "LED_OnOff";
boolean led_state = false;

using namespace websockets;

WebsocketsClient web_socket_client;
JSONVar send_object;

WiFiClientSecure wifi;
void connect_to_wifi()
{
  Serial.print("Connecting to SSID: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, wifipassword);

    while( WiFi.status() != WL_CONNECTED ) {
        Serial.print(".\n");
        delay(1000);
    }
    delay(2000);
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("Got IP ");
    Serial.println(WiFi.localIP());
}

void connect_to_websocket()
{
   while(!web_socket_client.connect(server_host_address, server_port, "/iot/device"))
    {
      Serial.println("Websocket Not Connected!!");
    }
    Serial.println(("Websocket Connected."));
    web_socket_client.send("PING");
    send_object["sensor_name"] = led_onoff;
    send_object["data"] = led_state;
    web_socket_client.send(JSON.stringify(send_object));

     // run callback when messages are received
    web_socket_client.onMessage([&](WebsocketsMessage message){
        JSONVar received_object = JSON.parse(message.c_str());
        const char *sensor_name = received_object["sensor_name"];
        if(led_onoff.equals(String(sensor_name)))
        {
          led_state = received_object["data"];
          digitalWrite(LED_PIN, led_state);
          send_object["sensor_name"] = led_onoff;
          send_object["data"] = led_state;
          web_socket_client.send(JSON.stringify(send_object));
        }
    });
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, led_state);
    connect_to_wifi();
    connect_to_websocket();
}

void loop() {
  web_socket_client.send("PING");
    if(web_socket_client.available()) {
        web_socket_client.poll();
    }
    delay(1000);
}




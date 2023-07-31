
#include <ArduinoWebsockets.h>
#include <Arduino_JSON.h>
#include <DHT22.h>

#define DHT22_DATA_PIN 4

const char* ssid = "nepaldigisys";
const char* wifipassword = "NDS_0ffice";
const char* server_host_address = "192.168.1.66";
const uint16_t server_port = 8080;

String humidity = "Humidity";
String temperature = "Temperature";

using namespace websockets;

WebsocketsClient web_socket_client;
JSONVar send_object;

DHT22 dht22(DHT22_DATA_PIN); 

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

     // run callback when messages are received
    web_socket_client.onMessage([&](WebsocketsMessage message){
        JSONVar received_object = JSON.parse(message.c_str());
        const char *sensor_name = received_object["sensor_name"];
        if(humidity.equals(String(sensor_name)))
        {
          Serial.println("Humidity data updated.");
        }
        else if (temperature.equals(String(sensor_name)))
        {
          Serial.println("Temperature data updated.");
        }
    });
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    connect_to_wifi();
    connect_to_websocket();
}

void loop() {
    if(web_socket_client.available()) {
        web_socket_client.poll();
    }
    float temp = 27.0;
    float humid = 63.5;
    send_object["sensor_name"] = temperature;
    send_object["data"] = temp;
    web_socket_client.send(JSON.stringify(send_object));

    delay(1000);

    send_object["sensor_name"] = humidity;
    send_object["data"] = humid;
    web_socket_client.send(JSON.stringify(send_object));

    delay(2000);

}




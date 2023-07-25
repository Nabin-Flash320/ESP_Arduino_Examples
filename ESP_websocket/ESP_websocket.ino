
#include <WiFiClientSecure.h>
#include <ArduinoWebsockets.h>


const char* ssid = "nepaldigisys";
const char* wifipassword = "NDS_0ffice";
const char* server_host_address = "192.168.1.66";
const uint16_t server_port = 8080;

using namespace websockets;

WebsocketsClient web_socket_client;

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

void setup() {
    Serial.begin(115200);
    delay(2000);
    connect_to_wifi();
    // Connect to websocker.
    while(!web_socket_client.connect(server_host_address, server_port, "/iot"))
    {
      Serial.println("Websocket Not Connected!!");
    }
    Serial.println(("Websocket Connected."));
    web_socket_client.send("PING");

     // run callback when messages are received
    web_socket_client.onMessage([&](WebsocketsMessage message){
        Serial.print("Got Message: ");
        Serial.println(message.data());
    });
}

void loop() {
    web_socket_client.send("PING");
    if(web_socket_client.available()) {
        web_socket_client.poll();
    }
    delay(1000);
}




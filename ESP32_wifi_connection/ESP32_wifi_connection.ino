
#include <WiFiClientSecure.h>

const char* ssid = "nepaldigisys";
const char* wifipassword = "NDS_0ffice";

WiFiClientSecure wifi;

void setup() {
    Serial.begin(115200);
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

void loop() {
    Serial.print(":");
    delay(1000);
}






#include <DHT22.h>

#define DHT22_DATA_PIN 4

DHT22 dht22(DHT22_DATA_PIN); 
 
void setup() {
  Serial.begin(115200); 
  Serial.println("\nCapturing data from DTH22");
  delay(2000);
}

void loop() {
  // Serial.println(dht22.debug()); 

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();

  Serial.print("Last Error: ");
  Serial.println(dht22.getLastError());

  Serial.print("humidity = ");
  Serial.print(h,1);
  Serial.print("\t");
  Serial.print("temperature = ");
  Serial.println(t,1);
  delay(1000);
}



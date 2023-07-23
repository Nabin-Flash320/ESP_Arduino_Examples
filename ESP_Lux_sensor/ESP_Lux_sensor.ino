
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

const int sda_pin = 2;
const int scl_pin = 1;

TwoWire lux_sensor_interface = TwoWire(0);
Adafruit_TSL2561_Unified lux_sensor = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT);

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing I2C interface...");
  lux_sensor_interface.setPins(sda_pin, scl_pin);
  lux_sensor_interface.begin();
  if(!lux_sensor.begin(&lux_sensor_interface))
  {
    Serial.println("TSL2561 connection error!");
    while(1);
  }
  Serial.println("TSL2561 lux sensor detected!!");

  sensor_t sensor;
  lux_sensor.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
  Serial.println("Configuring sensor...");
  lux_sensor.enableAutoRange(true);           
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
  
}

void loop()
{
  uint16_t broadband = 0;
  uint16_t ir = 0;
  sensors_event_t event;
  lux_sensor.getEvent(&event);
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" lux");
  }
  else
  {
    Serial.println("Sensor overload");
  }
  delay(2000);
}
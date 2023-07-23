
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define BLE_LED_SERVER_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define BLE_LED_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer *BLE_LED_Server = NULL;
BLEService *BLE_LED_Service = NULL;
BLECharacteristic *ESP_BLE_LED_on_characteristics = NULL;

class BLE_LED_on_off_callback: public BLECharacteristicCallbacks
{ 
  private:

    int LED_Pin;
    bool LED_state;

    void set_LED_state(bool led_state)
    {
      digitalWrite(LED_Pin, led_state);
      LED_state = led_state;
    }

    bool get_LED_state()
    {
      return LED_state;
    }

  public:

  BLE_LED_on_off_callback(int LED_pin_num = RGB_BUILTIN, bool led_state = false)
  {
    LED_Pin = LED_pin_num;
    LED_state = led_state;
    pinMode(LED_Pin, OUTPUT);
    digitalWrite(LED_Pin, LED_state);
  }

  void onWrite(BLECharacteristic *characteristic)
  {
    Serial.print("On-Off server data received.\n");
    const uint8_t *received_value = characteristic->getData();
    Serial.print("Received value is ");
    Serial.println(*received_value);
    if((0x00 == *received_value) || (0x01 == *received_value))
    {
      set_LED_state((0x00 == *received_value ? false : true));
    }
    else 
    {
      Serial.println("Wrong data received.");
    }
  }

  void onRead(BLECharacteristic *characteristic)
  {
    int response = get_LED_state();
    characteristic->setValue(response);
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE!");

  BLEDevice::init("BLE LED server");
  BLE_LED_Server = BLEDevice::createServer();
  BLE_LED_Service = BLE_LED_Server->createService(BLE_LED_SERVER_UUID);
  ESP_BLE_LED_on_characteristics = BLE_LED_Service->createCharacteristic(
                                         BLE_LED_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE                                       
                                         );
  ESP_BLE_LED_on_characteristics->setCallbacks(new BLE_LED_on_off_callback);
  BLE_LED_Service->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLE_LED_SERVER_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  delay(2000);
}
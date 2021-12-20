#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "a31e7f39-239b-4ccf-81d3-df44c325716f"
#define CHARACTERISTIC_UUID "8a8d440c-b1c7-4a97-af26-784211ee50f0"

static uint8_t outputData[1];
BLECharacteristic *pOutputChar;

class InputReceivedCallbacks: 
  public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharWriteState) {
      
        std::string response = pCharWriteState->getValue();
        Serial.print("you entered: ");
        for(int i=0; i<response.length();i++){
          Serial.print(response[i]);
        }
       
    }
};




void setup() {
  Serial.begin(115200);
  Serial.println("Establishing server!");
  BLEDevice::init("myESP");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                     CHARACTERISTIC_UUID,
                                     BLECharacteristic::PROPERTY_READ |
                                     BLECharacteristic::PROPERTY_WRITE
                                     );
  pCharacteristic->setCallbacks(new InputReceivedCallbacks());
  pService->start();
  
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}

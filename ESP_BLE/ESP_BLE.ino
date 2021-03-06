#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <ESP32Servo.h>

#define SERVICE_UUID "a31e7f39-239b-4ccf-81d3-df44c325716f"
#define CHARACTERISTIC_UUID "8a8d440c-b1c7-4a97-af26-784211ee50f0"

const byte gpio = 5;
Servo servo;

class InputReceivedCallbacks: 
  public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharWriteState) {
        std::string response = pCharWriteState->getValue();
        Serial.print("you entered: ");
        int inputTemp=0;
        for(int i=0; i<response.length();i++){
          Serial.print(response[i]);
          if(response[i]>=48 && response[i] <= 57){
            if(!inputTemp){
              inputTemp+= response[i]-48;
            }
            else{
              inputTemp*= 10;
              inputTemp+= (response[i]-48);
            }
          }
        }
        Serial.print(inputTemp);
        if(inputTemp){
          servo.write(inputTemp*8);
        }
       Serial.println();
    }
};




void setup() {
  //sets of BLE server
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
  //sets up Read/Write for server
  pCharacteristic->setCallbacks(new InputReceivedCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  servo.attach(gpio);
  servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}

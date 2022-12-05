/*
  Button LED
  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED and another characteristic that
  represents the state of the button.
  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button connected to pin 4
  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.
  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

const int firstModulePin = 13;
const int secondModulePin = 12;
const int thirdModulePin = 14;
const int fourthModulePin = 27;

bool currentFirstModuleValue = false;
bool currentSecondModuleValue = false;
bool currentThirdModuleValue = false;
bool currentFourthModuleValue = false;

BLEService relayFirstService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service
BLEByteCharacteristic firstModuleCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
// create switch characteristic and allow remote device to read and write to first relay module

BLEService relaySecondService("19B10020-E8F2-537E-4F6C-D104768A1214"); // create service
BLEByteCharacteristic secondModuleCharacteristic("19B10021-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
// create switch characteristic and allow remote device to read and write to second relay module

BLEService relayThirdService("19B10030-E8F2-537E-4F6C-D104768A1214"); // create service
BLEByteCharacteristic thirdModuleCharacteristic("19B10031-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
// create switch characteristic and allow remote device to read and write to third relay module

BLEService relayFourthService("19B10040-E8F2-537E-4F6C-D104768A1214"); // create service
BLEByteCharacteristic fourthModuleCharacteristic("19B10041-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
// create switch characteristic and allow remote device to read and write to fourth relay module

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  pinMode(firstModulePin, OUTPUT);
  pinMode(secondModulePin, OUTPUT);
  pinMode(thirdModulePin, OUTPUT);
  pinMode(fourthModulePin, OUTPUT);

  // begin initialization
  if (!BLE.begin())
  {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1)
      ;
  }

  // set the local name peripheral advertises
  BLE.setLocalName("Relê de 4 modulos controlado pela ESP32");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(relayFirstService);
  BLE.setAdvertisedService(relaySecondService);
  BLE.setAdvertisedService(relayThirdService);
  BLE.setAdvertisedService(relayFourthService);

  // add the characteristics to the service
  relayFirstService.addCharacteristic(firstModuleCharacteristic);
  relaySecondService.addCharacteristic(secondModuleCharacteristic);
  relayThirdService.addCharacteristic(thirdModuleCharacteristic);
  relayFourthService.addCharacteristic(fourthModuleCharacteristic);

  // add the service
  BLE.addService(relayFirstService);
  BLE.addService(relaySecondService);
  BLE.addService(relayThirdService);
  BLE.addService(relayFourthService);

  firstModuleCharacteristic.writeValue(0);
  secondModuleCharacteristic.writeValue(0);
  thirdModuleCharacteristic.writeValue(0);
  fourthModuleCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth® device active, waiting for connections...");
}

void loop()
{
  // poll for Bluetooth® Low Energy events
  BLE.poll();

  bool firstModuleChanged = (firstModuleCharacteristic.value() != currentFirstModuleValue);

  if (firstModuleChanged)
  {
    if (firstModuleCharacteristic.value())
    {
      Serial.println("First Module on");
      digitalWrite(firstModulePin, HIGH);
      currentFirstModuleValue = true;
    }
    else
    {
      Serial.println("First Module off");
      digitalWrite(firstModulePin, LOW);
      currentFirstModuleValue = false;
    }
  }

  bool secondModuleChanged = (secondModuleCharacteristic.value() != currentSecondModuleValue);

  if (secondModuleChanged)
  {
    if (secondModuleCharacteristic.value())
    {
      Serial.println("Second Module on");
      digitalWrite(secondModulePin, HIGH);
      currentSecondModuleValue = true;
    }
    else
    {
      Serial.println("Second Module off");
      digitalWrite(secondModulePin, LOW);
      currentSecondModuleValue = false;
    }
  }

  bool thirdModuleChanged = (thirdModuleCharacteristic.value() != currentThirdModuleValue);

  if (thirdModuleChanged)
  {
    if (thirdModuleCharacteristic.value())
    {
      Serial.println("Third Module on");
      digitalWrite(thirdModulePin, HIGH);
      currentThirdModuleValue = true;
    }
    else
    {
      Serial.println("Third Module off");
      digitalWrite(thirdModulePin, LOW);
      currentThirdModuleValue = false;
    }
  }

  bool fourthModuleChanged = (fourthModuleCharacteristic.value() != currentFourthModuleValue);

  if (fourthModuleChanged)
  {
    if (fourthModuleCharacteristic.value())
    {
      Serial.println("Fourth Module on");
      digitalWrite(fourthModulePin, HIGH);
      currentFourthModuleValue = true;
    }
    else
    {
      Serial.println("Fourth Module off");
      digitalWrite(fourthModulePin, LOW);
      currentFourthModuleValue = false;
    }
  }
}

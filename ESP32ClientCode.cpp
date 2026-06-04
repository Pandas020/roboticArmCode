//includes

#include <BLEDevice.h>



//Definintions

#define ONBOARD_LED 2


//GLOBALS
static BLEUUID serviceUUIDTarget("186ff4e3-45c7-4b73-8db2-6612a3278c2b"); //this is our target uuid  
static BLEUUID charUUIDTarget("ed0fe5c3-1064-47e5-b9d9-f6912652e16d"); //this is our target characteristic
static BLEAdvertisedDevice  *pTargetDevice; // pointer that points to BLEAdvertisedDevice


//Call Backs

class MyAdertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks{ //BLEAdvertisedDeviceCallbacks is a virtual function in our BLE device library and we are able to overwrite it 
  void onResult(BLEAdvertisedDevice advertisedDevice){ // we have access to the advertised device data from stuff like name or manunfactoring data

    Serial.print("BLE Advertised Device Found: "); //when found we are just going to print information off
    Serial.println(advertisedDevice.toString()); // we will do that by just using the tostring function
  //why advertised data is here is so that way when it ends so does the data 
    if(advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUIDTarget)){ // runs a check if it has a uuid and to see if it is advertising the specific service
      Serial.println("Target Service Found"); // called everytime a deviced is identified until finds the correct one 
      pTargetDevice = new BLEAdvertisedDevice(advertisedDevice); //create a new BLEAdvertised device using the info from the we got and we will save it on pTargetDevice and we take that UUID and save it into our own variable while saving it in pTargetDevice
    } //because we have the function BLEAdvertisedDevice we are allowed to use it here in this function and it is global as well 
  }  // we have to make a new instance of BLEAdvertisedDevice b/c if we had a pointer outside of this function then after it ends we would have a memory leak since the pointer is pointing to anything so we need an instance in this function to be able to combat that 

};

class MyClientCallbacks : public BLEClientCallbacks { // the 2 functions that we can create are onConnect and onDisconnect 

  void onConnect(BLEClient *pClient){ //when a device connects it turns on LED
    Serial.println("Connected ");
    digitalWrite(ONBOARD_LED, HIGH);
  }

  void onDisconnect(BLEClient *pClient){ //when a device disconnects it turns on LED
    Serial.println("Disconnected ");
    digitalWrite(ONBOARD_LED, LOW);
  }
};

void setup (){

  Serial.begin(9600);
  Serial.println();

  pinMode(ONBOARD_LED, OUTPUT);

  //BLE Device
  BLEDevice::init(""); //static function and no one is looking for you as a client 

  //Scan
  BLEScan* pBLEScan = BLEDevice::getScan();// we are creating the scan object, the getScan function returns a pointer being BLEScan which we created a variable to point to the BLEScan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdertisedDeviceCallbacks()); //sets the advertised device callbacks for our scans and the information will be sent after executed the callback
  pBLEScan -> setActiveScan(true); //we want the scan to be an active scan 
  pBLEScan -> start(5, false); // number of seconds that we want to scan and if we want it to start scanning wait then stop then start up again 
  //it is blocking the client for 5 seconds since we are waiting for the scan and then we are able to connect as the client 

  //Client
  BLEClient* pClient = BLEDevice::createClient(); //creating a client and put it in the variable pClient
  pClient ->setClientCallbacks(new MyClientCallbacks());
  pClient->connect(pTargetDevice); // we connect to the target device
  Serial.print("Connect to "); // print out what we are connected to 
  Serial.println(pTargetDevice->getName()); // then we can print the name as the pointer can get the name of it since we are connected to it 



  //show value of CHaracteristic 
  BLERemoteService * pRemoteService = pClient ->getService(serviceUUIDTarget); // the pClient gets the specific service by using the getService function which gets the service UUIDTarget  which stores in a pointer which is apart of the BLEREmoteService object
  BLERemoteCharacteristic * pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUIDTarget); // same as the service just for characteristic
  int value = pRemoteCharacteristic ->readUInt32(); // we are able to read the unsigned integer 
  Serial.print("The characteristic value was: "); // print on to screen
  Serial.println(value);


}
//btw very unsafe code after every check we should run 

//BLERemoteService * pRemoteService = pClient ->getService(serviceUUIDTarget); 
// if(pRemoteService == nullptr)
//   Serial.print("Failed to find our characteristic UUID: ")'
//      pClient->disconnect();



//if (pRemoteCharacteristic->canREad()){
//    BLERemoteCharacteristic * pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUIDTarget); // same as the service just for characteristic
//   int value = pRemoteCharacteristic ->readUInt32(); // we are able to read the unsigned integer 
//   Serial.print("The characteristic value was: "); // print on to screen
//   Serial.println(value);


// } // very safe code 

//why we dont is because we already know our server and our client so when it gets powerd on it will automatically be looking and connected + we dont need to have more devices to be connected so in 99% of use cases this is very unsafe/ need guards code but since we already can control most/all variables its okay 

void loop(){



}

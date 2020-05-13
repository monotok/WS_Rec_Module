#include <VirtualWire.h>
#include <stdio.h>
#include <dht.h>
#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>

#define DHT22_PIN 9
#define SLAVE_ADDRESS 0x04

dht DHT;
Thread myThread = Thread();

//Constant values
const int receive_pin = 8;
const int receive_LED = 3;
const int dhterror_LED = 10;

//Globals
char result[4];
float tempFromSensor, perBattLeft;
float t; //temp value
int chk;
long errorC = 0;
long okC = 0;
uint8_t whichStructToSend = 0;

struct sensor_Data 
{
  uint16_t temperature;
  char sensorID[10];
  uint16_t perBatt;
}tempSensorValues;

struct local_Data
{
  uint16_t temperature; 
  char sensorID[10];
  uint16_t humidity;
}local;

union sensorStructToSendViaI2C
{
  sensor_Data tempSensorValues;
  byte packet[sizeof(sensor_Data)];
};
sensorStructToSendViaI2C ssts;

union localStructToSendViaI2C
{
  local_Data local;
  byte packet[sizeof(local_Data)];
};
localStructToSendViaI2C lsts;

void getDHT22()
{
  chk = DHT.read22(DHT22_PIN);
  switch (chk)
    {
    case DHTLIB_OK:
        digitalWrite(dhterror_LED, LOW);
        lsts.local.temperature = (uint16_t)(DHT.temperature*100);
        lsts.local.humidity = (uint16_t)(DHT.humidity*100);
        okC++;
        break;
    default:
        digitalWrite(dhterror_LED, HIGH);
        errorC++;
        break;
    }
}

// callback for sending data
void sendData()
{
 //Wire.write((byte *) &tempSensorValues, sizeof tempSensorValues);
 if(whichStructToSend == 1)
 {
  Wire.write(ssts.packet, sizeof(sensor_Data));
 }
 else
 {
  Wire.write(lsts.packet, sizeof(local_Data));
 }
 
// int len = sizeof(struct sensor_Data);
// Serial.println(len);
// char test[len];
// memcpy(test, &tempSensorValues, len);
//Wire.write(test, len);

 //memcpy(&doesitwork, test, len); Copies to another struct variable

}
void receiveData(int numBytes)
{
 int number;
 while(Wire.available()) 
 {
  number = Wire.read();
  if (number == 0)
  {
    whichStructToSend = 0;
  }
  else
  {
    whichStructToSend = 1; 
  }
 }
}

void setup() 
{
  delay(1000);
  Serial.begin(9600);
  pinMode(receive_LED, OUTPUT);
  pinMode(dhterror_LED, OUTPUT);

  //RF Setup
  vw_set_rx_pin(receive_pin);
  vw_setup(2000);   // Bits per sec
  vw_rx_start(); 

  //Thread stuff so I can transmit every so often
  myThread.enabled = true; // Default enabled value is true
  myThread.setInterval(2000); // Setts the wanted interval to be 10ms
  myThread.onRun(getDHT22);

  // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);

 strcpy(lsts.local.sensorID,"Here");
}

void loop() 
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;
  
    digitalWrite(receive_LED, HIGH); // Flash a light to show received good message
    
    // Message with a good checksum received, dump it.

    if(buflen == sizeof(sensor_Data)); //If the structures are the same size then copy data into structure
    {
      memcpy(&ssts.tempSensorValues, buf, sizeof(sensor_Data));
    }
    
//    for (i = 0; i < buflen; i++)
//    {
//        result[i] = (char)buf[i];
//    }
//    t = atoi(result);
    tempFromSensor = ((float)ssts.tempSensorValues.temperature/100);
    perBattLeft = ((float)ssts.tempSensorValues.perBatt/100);

//    Serial.print(tempFromSensor);
//    Serial.print(":");
//    Serial.print(ssts.tempSensorValues.sensorID);
//    Serial.print(":");
//    Serial.print(perBattLeft);
   // Serial.print(":");
   // Serial.print(lsts.local.temperature);
   // Serial.print(":");
   // Serial.print(lsts.local.humidity);
//    Serial.print(":");
//    Serial.print("Error");
//    Serial.print(errorC);
//    Serial.print(":");
//    Serial.print("Ok");
//    Serial.print(okC);
//    Serial.print("\n");
    delay(100);
    digitalWrite(receive_LED, LOW);
  }
  if(myThread.shouldRun())
  {
    // Yes, the Thread should be runned, let's run it
    myThread.run();
  }
  

}

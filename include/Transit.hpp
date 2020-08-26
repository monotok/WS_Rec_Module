//
// Created by hammer on 01/07/2020.
//

#ifndef REMOTESENSORS_TRANSIT_HPP
#define REMOTESENSORS_TRANSIT_HPP

#include <RH_ASK.h>
#include <SPI.h>
#include <Abc_Sensor.hpp>

class Transit
{
public:
    Transit(int ledPin, int radioReceivePin): ledPin(ledPin), Radio(2000, radioReceivePin, 0, 0) {
        pinMode(ledPin, OUTPUT);
    }

    void ReceiveSensor(Sensor &sensors);
    void initialise();

private:
    const int ledPin;
    RH_ASK Radio;
    uint8_t sensorBuffer[40];
    uint8_t sensorBufferLength = sizeof(sensorBuffer);
};


#endif //REMOTESENSORS_TRANSIT_HPP

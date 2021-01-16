//
// Created by hammer on 12/11/2020.
//

#ifndef WS_REC_MODULE_LOCALSENSOR_HPP
#define WS_REC_MODULE_LOCALSENSOR_HPP

#include <Wire.h>
#include <Abc_Sensor.hpp>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define ERR_FOUND 0
#define ERR_NOT_FOUND 1

class LocalSensor
{
public:
    LocalSensor(uint8_t cs_pin, uint8_t ledErrPin);
    void initialise();
    void processTemperature(Sensor& sensors);
    void processHumidity(Sensor& sensor);
    void processPressure(Sensor& sensor);

private:
    void flashErrLed();

    Adafruit_BME280 bme;
    uint8_t ledErrPin;
    uint8_t errInitialising = ERR_NOT_FOUND;
};


#endif //WS_REC_MODULE_LOCALSENSOR_HPP

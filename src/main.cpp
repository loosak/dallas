#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "secrets.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 21

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

const long interval = 1000;

void toggleBuiltin()
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Dallas Temperature IC Control Library Demo");
    // Start up the library
    sensors.begin();
}

void loop() //loop() gets called about 40,000 times a second?
{
    if (!(millis() % interval))
    {
        toggleBuiltin();
        Serial.print(" Requesting temperatures...");
        sensors.requestTemperatures(); // Send the command to get temperature readings
        Serial.println("DONE");
        Serial.print("Temperature is: ");
        Serial.println(sensors.getTempCByIndex(0)); // 0 refers to the first IC on the wire
        toggleBuiltin();
    }
}
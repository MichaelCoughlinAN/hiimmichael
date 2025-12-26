// Michael Coughlin
// hiimmichael.com
// © 2020

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <Wire.h>

const unsigned long SECOND = 1000;
const unsigned long HOUR = 3600 * SECOND;
const int sensorPin = A0; // Set analog pin for moisture sensor

// Take soil moisture reading from analog sensor
int getSoilMoisture() {
    int sensorValue = 0;
    sensorValue = analogRead(sensorPin);
    return sensorValue;
}

void setup() {
    Serial.begin(115200);
    delay(100);
}
 
void loop() { 
    int soilMoisture = getSoilMoisture();
    
    // TODO: Send data to web server via HTTP or MQTT  
 
    delay(1*HOUR);
}

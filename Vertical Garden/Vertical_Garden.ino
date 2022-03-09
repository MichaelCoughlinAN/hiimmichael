// Michael Coughlin
// hiimmichael.com
// © 2021

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <HttpClient.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PIN   14
#define N_LEDS 1
#define SERIESRESISTOR 560    
#define SENSORPIN A0

const unsigned long MILLISECOND = 100;
const unsigned long SECOND = MILLISECOND * 10;
const unsigned long MINUTE = 60000;
const unsigned long HOUR = 60 * MINUTE;

const char* ssid = "";
const char* password = "";

const char* host = "";
const int httpPort = 80;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB);

float getLevelReading() {
  Serial.println("Taking fluid level reading ... ");
  delay(3 * SECOND);
  
  float reading = analogRead(SENSORPIN);
  Serial.println(reading);
  return reading; 
}

void setup(void) {
  WiFi.softAPdisconnect(true);
  Serial.begin(9600);
  delay(3 * MILLISECOND);
  
  strip.setBrightness(255);
  strip.begin();
  delay(3 * MILLISECOND);
  
  strip.setPixelColor(0,strip.Color(0,0,0));
  strip.show();
  delay(3 * MILLISECOND);
}
 
void loop(void) { 
  Serial.print("\n\nConnecting to WiFi network ... ");
  Serial.println(ssid);
    
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(5 * MILLISECOND);
    }
  }
   
  Serial.println("\nWiFi connected!");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    
  WiFiClient client;
  
  float level = (getLevelReading() + getLevelReading() + getLevelReading()) / 3.0;
  
  // Do something with level data
  
  rainbow(10);
  
  strip.setPixelColor(0, strip.Color(0,0,0));
  strip.show();
  
  Serial.println("\nGoing to sleep now ...");
  delay(60 * MINUTE);
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); ++i) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    
    strip.show();
    delay(wait);
  }
}

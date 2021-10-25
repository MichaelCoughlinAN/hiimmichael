// Michael Coughlin
// hiimmichael.com
// 2021

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#define LED_PIN 14
#define LED_COUNT 24

const char* host     = "";
const char* ssid     = "";
const char* password = "";

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

int oldR[LED_COUNT];
int oldG[LED_COUNT];
int oldB[LED_COUNT];
int newR[LED_COUNT];
int newG[LED_COUNT];
int newB[LED_COUNT];
int nmax = 255;

void Sunset() {
  for (int i = 0; i < LED_COUNT; ++i) {
    newR[i] = random(100, 256); // Red
    newG[i] = random(120);
    newB[i] = random(100);
  }

  for (int n = 0; n < 256; ++n) { // Update over time
    for (int i = 0; i < LED_COUNT; ++i) { // Update each pixel
      int thisR = map(n, 0, nmax, oldR[i], newR[i]);
      int thisG = map(n, 0, nmax, oldG[i], newG[i]);
      int thisB = map(n, 0, nmax, oldB[i], newB[i]);
      strip.setPixelColor(i, thisR, thisG, thisB);
    }

    strip.show();
    delay(10);
  }

  for (int i = 0; i < LED_COUNT; ++i) {
    oldR[i] = newR[i];
    oldG[i] = newG[i];
    oldB[i] = newB[i];
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.print("Initializing NeoPixel strip object ... ");
  strip.begin();
  
  delay(100);
  strip.show();

  Serial.print("[SUCCESS]\n");
  Serial.print("\n\nConnecting to WiFi ");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print(" [SUCCESS]\n");
}

void loop() {
  // Display a simple sunset animation
  Sunset();
}

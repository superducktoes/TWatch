#include "WiFi.h"


void wifiScanner() {

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  ttgo->tft->print("scanning...");
  int n = WiFi.scanNetworks();

  ttgo->tft->fillScreen(TFT_BLACK);

  int yPos = 0;
  ttgo->tft->setCursor(0, yPos);
  for (int i = 0; i < n; i++) {

    yPos = yPos +  20;
    ttgo->tft->setCursor(0, yPos);
    String wifiName = WiFi.SSID(i);

    if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
      ttgo->tft->setTextColor(TFT_RED);
    } else {
      ttgo->tft->setTextColor(TFT_GREEN);
    }

    ttgo->tft->print(wifiName);

    /*
       I dont know how many lines can be displayed at once but if we reach the limit of lines
       sleep for 10 seconds so we can read the screen and then clear it and keep going
    */

    if ( (i != 0) && (i % 9  == 0) ) {
      yPos = 0;
      delay(10000);
      ttgo->tft->fillScreen(TFT_BLACK);
    }

  }

  // Wait for touch to return
  int16_t x, y;
  while (!ttgo->getTouch(x, y)) {} // Wait for touch
  while (ttgo->getTouch(x, y)) {}  // Wait for release
  ttgo->tft->fillScreen(TFT_BLACK);
}

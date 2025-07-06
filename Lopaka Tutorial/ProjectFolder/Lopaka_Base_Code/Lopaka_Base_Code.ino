#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup(void) {
  tft.init();

  tft.setRotation(1);
  
  tft.fillScreen(0x0000);

  //draw();
}

void loop() {
}
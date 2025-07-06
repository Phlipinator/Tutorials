#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

int counter = 0;
int pauseTime = 200;

void setup(void) {
  tft.init();

  tft.setRotation(1);
  
  tft.fillScreen(0x0000);

  draw();
}

void draw(void) {
    tft.drawRect(20, 56, 120, 16, 0xFFFF);

    tft.fillRect(22, 58, 12, 12, 0xFFFF);

    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.setFreeFont();
    tft.drawString("Simple Loading Screen", 18, 27);
}

void loop() {
  if(counter < 9){
    tft.fillRect((22+ counter * 13), 58, 12, 12, 0xFFFF);
    counter++;
    delay(pauseTime);
  }else{
    counter = 0;
    tft.fillScreen(0x0000);
    draw();
    delay(pauseTime);
  }
}

#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

TFT_eSPI tft = TFT_eSPI();

#define SDA_PIN 33
#define SCL_PIN 32

Adafruit_BMP280 bmp280;

void setup(void) {
  tft.init();

  tft.setRotation(1);
  
  tft.fillScreen(0x0000);

  draw();

  Wire.begin(SDA_PIN, SCL_PIN);
  // 0x76 is a common I2C address for the BMP280
  bmp280.begin(0x76);
}

static const unsigned char PROGMEM image_cloud_download_bits[] = {0x00,0x00,0x00,0x07,0xc0,0x00,0x08,0x20,0x00,0x10,0x10,0x00,0x30,0x08,0x00,0x40,0x0e,0x00,0x80,0x01,0x00,0x80,0x00,0x80,0x40,0x80,0x80,0x3c,0x9f,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x03,0xe0,0x00,0x01,0xc0,0x00,0x00,0x80,0x00,0x00,0x00,0x00};

static const unsigned char PROGMEM image_weather_temperature_bits[] = {0x1c,0x00,0x22,0x02,0x2b,0x05,0x2a,0x02,0x2b,0x38,0x2a,0x60,0x2b,0x40,0x2a,0x40,0x2a,0x60,0x49,0x38,0x9c,0x80,0xae,0x80,0xbe,0x80,0x9c,0x80,0x41,0x00,0x3e,0x00};

void draw(void) {
    tft.setTextColor(0xFFFF);
    tft.setTextSize(3);
    tft.setFreeFont();
    tft.drawString("BMP280", 28, 7);

    tft.drawLine(0, 33, 159, 33, 0xFFFF);

    tft.drawBitmap(6, 55, image_cloud_download_bits, 17, 16, 0xFFFF);

    tft.drawBitmap(7, 82, image_weather_temperature_bits, 16, 16, 0xFFFF);
}

void loop() {
  float temperature = bmp280.readTemperature();
  float pressure = bmp280.readPressure();

  tft.setTextSize(1);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.drawString(String(pressure), 28, 59);
  tft.drawString(String(temperature), 28, 87);

  delay(500);
}
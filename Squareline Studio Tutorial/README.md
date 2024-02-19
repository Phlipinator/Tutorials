## Overview

This note provides a guide on how to build UIs for _TFT Displays_ using _Squareline Studio_. The guide will be focused on the round _GC9A01 display_ and will also briefly explain how to set everything up as well as how to interact with UI elements using code.
_Squareline Studio_ can be downloaded [here](https://squareline.io/).

## Project Setup

When creating a new project, choose the following Options for the _GC9A01_:
![Squareline Studio Project Template](SquarelineStudio_ProjectTemplate.png 'Squareline Studio Project Template')
For the _Theme_, you can of course choose whatever you like, but it is important to choose a _color depth_ of _16 bit_, or the UI will not display correctly.

## Export

Once you have created your project and designed everything how you want it to be, go to _Export → Create Template Project_ and choose your Arduino-Folder as destination.

## Configuration

For everything to work correctly, some changes in the configuration of the _TFT_eSPI_ library, that automatically gets downloaded and placed into your chosen folder, need to be made.
Go to your Arduino folder and then to _ProjectName → libraries → TFT_eSPI_.
There, you can either choose to modify _User_Setup.h_ according to your needs (un-comment the correct driver and Pin Configuration) or open the _User_Setup_Select.h_ file and search for your Board-Display combination.
In this case, comment out this line

```cpp
#include <User_Setup.h>
```

and un-comment this line:

```cpp
#include <User_Setups/Setup46_GC9A01_ESP32.h>
```

In the folder _User_Setups_, you will be able to find said file _Setup46_GC9A01_ESP32.h_ and see the standard PinOut for the microcontroller.

## PinOut

The Standard Configuration looks like this:

```cpp
// See SetupX_Template.h for all options available
#define USER_SETUP_ID 46

#define GC9A01_DRIVER

#define TFT_MISO 19 // Not needed
#define TFT_MOSI 23 // SDA
#define TFT_SCLK 18 // SCL
#define TFT_CS    15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)

#define LOAD_GLCD  // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2 // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4 // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6 // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7 // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8 // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts
#define SMOOTH_FONT

#define SPI_FREQUENCY 40000000

#define SPI_READ_FREQUENCY 20000000

#define SPI_TOUCH_FREQUENCY 2500000

// #define SUPPORT_TRANSACTIONS
```

This wiring diagram is for the [[ESP32 DEVKIT V1]], but any _ESP32_ based board should work the same.
![Wiring Diagram](Wiring_Diagram.png 'Wiring Diagram')

## Arduino IDE

In the _Arduino IDE_, first go to _Preferences_ and set your _Sketchbook location_ to the project folder that we created earlier. This way the libraries don’t get mixed up.

If you want to interact with the elements you created in _Squareline Studio_, you can do this by adding this declaration:

```cpp
extern lv_obj_t * ui_NameOfYourAsset;
```

This then can be manipulated like this, for example:

```cpp
// Rotate an image asset to 100 degrees
lv_img_set_angle(NameOfYourAsset, 100);
```

/************************************************************************
 * 
 * ESP8266 NodeMCU Interface with ST7789 TFT display (240x240 pixel)
 *   and BMP280 barometric pressure & temperature sensor.
 *
 ************************************************************************/

#include <Wire.h>              // Wire library (required for I2C devices)
#include <Adafruit_GFX.h>      // Adafruit core graphics library
#include <Adafruit_ST7789.h>   // Adafruit hardware-specific library for ST7789
#include <Adafruit_BMP280.h>   // Adafruit BMP280 sensor library

// ST7789 TFT module connections
#define TFT_DC    D3     // TFT DC  pin is connected to NodeMCU pin D3 (GPIO0)
#define TFT_RST   D4     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    D8     // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)
// initialize ST7789 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// define device I2C address: 0x76 or 0x77 (0x77 is library default address)
#define BMP280_I2C_ADDRESS  0x76
// initialize Adafruit BMP280 library
Adafruit_BMP280  bmp280;

void setup(void) {

  // initialize the ST7789 display (240x240 pixel)
  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2);

  // if the screen is flipped, remove this command
  tft.setRotation(2);
  // fill the screen with black color
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);         // turn off text wrap option

  // initialize the BMP280 sensor
  Wire.begin(D2, D1);  // set I2C pins [SDA = D2, SCL = D1], default clock is 100kHz
  if( bmp280.begin(BMP280_I2C_ADDRESS) == 0 ) {
    // connection error or device address wrong!
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);   // set text color to white and black background
    tft.setTextSize(4);      // text size = 4
    tft.setCursor(3, 88);    // move cursor to position (3, 88) pixel
    tft.print("Connection");
    tft.setCursor(63, 126);  // move cursor to position (63, 126) pixel
    tft.print("Error");
    while(1);  // stay here
  }

  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);  // set text color to green and black background
  tft.setTextSize(3);         // text size = 3
  tft.setCursor(17, 31);      // move cursor to position (17, 31) pixel
  tft.print("TEMPERATURE:");
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);  // set text color to yellow and black background
  tft.setCursor(44, 140);   // move cursor to position (44, 140) pixel
  tft.print("PRESSURE:");
  tft.setTextSize(4);       // text size = 4
  // print "°C"
  tft.drawCircle(171, 77, 4, ST77XX_RED);
  tft.drawCircle(171, 77, 5, ST77XX_RED);
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  // set text color to yellow and black background
  tft.setCursor(180, 71);
  tft.print("C");

}

// main loop
void loop() {

  delay(1000);    // wait a second

  // read temperature and pressure from BMP280 sensor
  float temp     = bmp280.readTemperature();   // get temperature
  float pressure = bmp280.readPressure();      // get pressure

  // print temperature (in °C)
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  // set text color to yellow and black background
  tft.setCursor(15, 71);
  if(temp < 0)    // if temperature < 0
    tft.printf( "-%02u.%02u", (int)abs(temp), (int)(abs(temp) * 100) % 100 );
  else            // temperature >= 0
    tft.printf( " %02u.%02u", (int)temp, (int)(temp * 100) % 100 );

  // 2: print pressure (in hPa)
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);  // set text color to cyan and black background
  tft.setCursor(0, 181);
  tft.printf( "%04u.%02uhPa", (int)(pressure/100), (int)((uint32_t)pressure % 100) );

}

// end of code.

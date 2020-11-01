#include <string.h>
#include "LedStrip.h"


uint16_t LedStrip::stripLen;

CRGB leds[NUMBER_LEDSTRIP][MaxLedsPerStrip];

LedStrip::LedStrip(uint32_t numPerStrip)
{
  stripLen = numPerStrip;
}

void LedStrip::begin(void) {
  if (LEDSTRIP_LENGTH1) FastLED.addLeds<LED_TYPE, DATA_PIN1, COLOR_ORDER>(leds[0], LEDSTRIP_LENGTH1).setCorrection(CRGB(BRIGHTNESS_PIN1,BRIGHTNESS_PIN1,BRIGHTNESS_PIN1) );
  if (LEDSTRIP_LENGTH2) FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(leds[1], LEDSTRIP_LENGTH2).setCorrection(CRGB(BRIGHTNESS_PIN2,BRIGHTNESS_PIN2,BRIGHTNESS_PIN2) );
  if (NUMBER_LEDSTRIP > 2)
    if (LEDSTRIP_LENGTH3) FastLED.addLeds<LED_TYPE, DATA_PIN3, COLOR_ORDER>(leds[2], LEDSTRIP_LENGTH3).setCorrection(CRGB(BRIGHTNESS_PIN3,BRIGHTNESS_PIN3,BRIGHTNESS_PIN3) );
  if (NUMBER_LEDSTRIP > 3)
    if (LEDSTRIP_LENGTH4) FastLED.addLeds<LED_TYPE, DATA_PIN4, COLOR_ORDER>(leds[3], LEDSTRIP_LENGTH4).setCorrection(CRGB(BRIGHTNESS_PIN4,BRIGHTNESS_PIN4,BRIGHTNESS_PIN4) );
  if (NUMBER_LEDSTRIP > 4)
    if (LEDSTRIP_LENGTH5) FastLED.addLeds<LED_TYPE, DATA_PIN5, COLOR_ORDER>(leds[4], LEDSTRIP_LENGTH5).setCorrection(CRGB(BRIGHTNESS_PIN5,BRIGHTNESS_PIN5,BRIGHTNESS_PIN5) );
  if (NUMBER_LEDSTRIP > 5)
    if (LEDSTRIP_LENGTH6) FastLED.addLeds<LED_TYPE, DATA_PIN6, COLOR_ORDER>(leds[5], LEDSTRIP_LENGTH6).setCorrection(CRGB(BRIGHTNESS_PIN6,BRIGHTNESS_PIN6,BRIGHTNESS_PIN6) );

  //FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither( 0 );
}

void LedStrip::show(void)
{
  FastLED.show();
}

void LedStrip::setStripLength(uint16_t length)
{
  stripLen = length;
  /*  FastLED[0].setLeds(leds[0], stripLen);
    FastLED[1].setLeds(leds[1], stripLen);
    FastLED[2].setLeds(leds[2], stripLen); */
}

void LedStrip::clearAll() {
  if (LEDSTRIP_LENGTH1) memset( &leds[0], 0, LEDSTRIP_LENGTH1* sizeof( CRGB) );
  if (LEDSTRIP_LENGTH2) memset( &leds[1], 0, LEDSTRIP_LENGTH2* sizeof( CRGB) );
  if (LEDSTRIP_LENGTH3) memset( &leds[2], 0, LEDSTRIP_LENGTH3* sizeof( CRGB) );
  if (LEDSTRIP_LENGTH4) memset( &leds[3], 0, LEDSTRIP_LENGTH4* sizeof( CRGB) );
  if (LEDSTRIP_LENGTH5) memset( &leds[4], 0, LEDSTRIP_LENGTH5* sizeof( CRGB) );
  if (LEDSTRIP_LENGTH6) memset( &leds[5], 0, LEDSTRIP_LENGTH6* sizeof( CRGB) );
}

void LedStrip::setPixels(uint32_t start_num,uint16_t len,int color)
{
  uint32_t strip, offset;
  char r=((color >> 16) & 0xFF);
  char g=((color >> 8) & 0xFF);
  char b=(color & 0xFF);

  strip = start_num >> 10; /// stripLen;
  offset = start_num & 1023; //% stripLen;

  for (uint16_t i=len;i;i--) {
    leds[strip][offset].b = b;
    leds[strip][offset].g = g;
    leds[strip][offset].r = r;
    offset++;
    /*if (offset==stripLen) { //should never happen
      offset=0;
      strip++;
    }*/
  }
}

void LedStrip::setPixel(uint32_t num, int color)
{
  uint32_t strip, offset;

  strip = num >> 10; /// stripLen;
  offset = num & 1023; //% stripLen;

  leds[strip][offset].b = (color & 0xFF); // Take just the lowest 8 bits.
  leds[strip][offset].g = ((color >> 8) & 0xFF); // Shift the integer right 8 bits.
  leds[strip][offset].r = ((color >> 16) & 0xFF); // Shift the integer right 8 bits.
}

int LedStrip::getPixel(uint32_t num)
{
  uint32_t strip, offset;

  strip = num >> 10; /// stripLen;
  offset = num & 1023; //% stripLen;
  return leds[strip][offset];
}

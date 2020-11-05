#include <string.h>
#include "LedStrip.h"


uint16_t LedStrip::stripTotalLen;
uint16_t LedStrip::stripLen[NUMBER_LEDSTRIP];
uint16_t LedStrip::stripStartOffset[NUMBER_LEDSTRIP];
uint8_t LedStrip::stripIndex[NUMBER_LEDSTRIP*MaxLedsPerStrip];

CRGB leds[NUMBER_LEDSTRIP][MaxLedsPerStrip];

LedStrip::LedStrip(uint32_t numPerStrip)
{
  stripTotalLen = numPerStrip;
  int offset=0;
  for (int j=0;j<NUMBER_LEDSTRIP;j++) {
    stripStartOffset[j]=offset;
    for (int i=0;i<stripTotalLen;i++) stripIndex[offset++]=j;
  } 
}

void LedStrip::begin(void) {
  int offset=0;
  for (int j=0;j<NUMBER_LEDSTRIP;j++) {
    stripStartOffset[j]=offset;
    for (int i=0;i<stripTotalLen;i++) stripIndex[offset++]=j;
  } 
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

void LedStrip::addNewStrip(uint8_t index,uint16_t length) {
  if ((index>=0)&&(index<NUMBER_LEDSTRIP)&&length&&(length<MaxLedsPerStrip)) FastLED[index].setLeds(leds[index],length);
}

void LedStrip::show(void)
{
  FastLED.show();
}

void LedStrip::setStripLength(uint16_t length)
{
  stripTotalLen = length;
  int offset=0;
  for (int j=0;j<NUMBER_LEDSTRIP;j++) {
    stripStartOffset[j]=offset;
    for (int i=0;i<stripTotalLen;i++) stripIndex[offset++]=j;
  }
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

  strip = stripIndex[start_num];//start_num / stripLen;
  offset = start_num-stripStartOffset[strip];// % stripLen;

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

  strip = stripIndex[num];//start_num / stripLen;
  offset = num-stripStartOffset[strip];// % stripLen;

  leds[strip][offset].b = (color & 0xFF); // Take just the lowest 8 bits.
  leds[strip][offset].g = ((color >> 8) & 0xFF); // Shift the integer right 8 bits.
  leds[strip][offset].r = ((color >> 16) & 0xFF); // Shift the integer right 8 bits.
}

int LedStrip::getPixel(uint32_t num)
{
  uint32_t strip, offset;

  strip = stripIndex[num];//start_num / stripLen;
  offset = num-stripStartOffset[strip];// % stripLen;
  
  return leds[strip][offset];
}

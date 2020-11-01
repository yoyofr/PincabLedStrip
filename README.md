# What is it ?
A fork of https://github.com/aetios50/PincabLedStrip improving significantly performances for Wemos D1 mini pro driven addressable leds (WS2812). DOF effects are smooth and responsive compared to initial firmware. 
Still a WIP.

# Important notes
Your **cabinet.xml** file needs to be adapted to use a 2Mbs serial connection

    <ComPortBaudRate>2000000</ComPortBaudRate> 

**LedStrip.h** to be edited to fit your own usage, basically 6 led strips linked to the 6 pins. Here's an example using 4 led strips :

    //Defines the number of ledstrip
	#define NUMBER_LEDSTRIP 4
	define LEDSTRIP_LENGTH1 70*6 //backboard
    #define LEDSTRIP_LENGTH2 24*2 //speakers ring
    #define LEDSTRIP_LENGTH3 117 //sideboard left
    #define LEDSTRIP_LENGTH4 117 //sideboard right
    #define LEDSTRIP_LENGTH5 0 //undercab+backbox
    #define LEDSTRIP_LENGTH6 0 //N/A

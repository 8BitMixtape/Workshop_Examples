/* 
 *  This code needs "Reset disabled" set via fusebits
 *  avrdude -P /dev/ttyACM0 -b 19200 -c avrisp -p t85 -U efuse:w:0xfe:m -U hfuse:w:0x5d:m -U lfuse:w:0xe1:m

=========================================================================================================
 _____  ______ _ _      ___  ____      _                       _   _  _____ _____ 
|  _  | | ___ (_) |     |  \/  (_)    | |                     | \ | ||  ___|  _  |
 \ V /  | |_/ /_| |_    | .  . |___  _| |_ __ _ _ __   ___    |  \| || |__ | | | |
 / _ \  | ___ \ | __|   | |\/| | \ \/ / __/ _` | '_ \ / _ \   | . ` ||  __|| | | |
| |_| | | |_/ / | |_    | |  | | |>  <| || (_| | |_) |  __/   | |\  || |___\ \_/ /
\_____/ \____/|_|\__|   \_|  |_/_/_/\_\\__\__,_| .__/ \___|   \_| \_/\____/ \___/ 
                                             | |                              
     https://8bitmixtape.github.io/          |_|                    
    .------------------------------.                              ATTINY85 Pins
    |↓↓\ 0  0  0  0  0  0  0  0 /↑↑|                              =============
    |   \___8Bit Mixtape NEO___/   |                                 _______
    |        __  ______  __        |                                |   U   |                                     
    |       /  \|\.....|/  \       |       (SYNC-OUT) <- D5/A0  PB5-|       |- VCC                                
    |       \__/|/_____|\__/       |   SD -> *SD-prog -> D3/A3  PB3-| ATTINY|- PB2  D2/A1 <- POTI_RIGHT
    |   ________________________   |   POTI_LEFT / CV -> D4/A2  PB4-|   85  |- PB1  D1    -> PWM SOUND
    |  |v2.0 hardware by dusjagr|  |                            GND-|       |- PB0  D0    -> NEOPIXELS
    '=============================='                                |_______|
  * based on TinyAudioBoot and hex2wav by Chris Haberer, Fredrik Olofsson, Budi Prakosa
    https://github.com/ChrisMicro/AttinySound
    
=========================================================================================================
The Center for Alternative Coconut Research presents: Happy Larson!
-----------------------------------------------------
  A Larson scanner (aka KITT style LED feature) for the hardware "8Bit Mixtape NEO"
  Because whenever you have more than 5 LEDs, Larson scanners are a must!
*********************************************************************************************************
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
********************************************* list of outhors *******************************************
  v0.1  09.12.2017 -G-A-N-D-A-L-F-  initial version of a proper larson scanner
  v0.2  10.12.2017 -G-A-N-D-A-L-F-  improved brightness & speed control, added oneliner audio
  v0.3  11.12.2017 -D-U-S-J-A-G-R-  improved audio
  v1.0  12.12.2017 -G-A-N-D-A-L-F-  cleaned up code & improved documentation
  v1.1  13.12.2017 -D-U-S-J-A-G-R-  added sync-out

  
  It is mandatory to keep the list of authors in this code.
  Please add your name if you improve/extend something
   _          _             
 _| |_ _ ___ |_|___ ___ ___ 
| . | | |_ -|| | .'| . |  _|
|___|___|___|| |__,|_  |_|  
           |___|   |___|    
****************************************************************************************************** */


// include 8BitMixTape NEO functions
#include "neolib.h"

// define some variables to be used in our code
int pos = 0; // current position of larson scanner
int dir = 1; // direction in which we're moving
int bright = 0; // brightness, a variable tuned by left poti
int wait = 0; // speed, a variable tuned by right poti

int snd = 0; // the tone to play
long t = 0; // timer variable
uint16_t p1 = 0; // modulate the tone, tuned by right poti

int syncPin = 5;

// things that need to happen once, upon startup
void setup() 
{
  // initialize 8BitMixTape NEO
  neobegin();
  pinMode(syncPin, OUTPUT);
        digitalWrite(syncPin,HIGH);
      delay(0);
      digitalWrite(syncPin,LOW);
}

// our main loop. we'll keep doing this for eternity!
void loop() 
{
  
  // generate some cool sound output
  // ripped from NEO_8Pixel-OneLiners
  uint16_t valuePoti = analogRead(POTI_RIGHT);
  p1 = 1023 - valuePoti>>5;
  snd = (t|3) * ((t>>1|t>>6)&p1&t>>3);
  digitalWrite (SPEAKERPIN, snd);
  t++;

  
  // update LEDs every 150 sound-cycles
  if (t % 8 == 0) {
    
    setColorAllPixel  ( COLOR_BLACK ); // clear all pixels
    
    bright = map (getPoti( POTI_RIGHT ), 0, 1023, 10, 255); // map brightness to left poti
    wait = map (getPoti( POTI_LEFT ), 0, 1023, 5000, 0); // map speed to right poti

    // define purple knight rider LED 'image' in a certain position
    pixels.setPixelColor(pos -4, bright/20, 0, bright/20);
    pixels.setPixelColor(pos -3, bright/13, 0, bright/13);
    pixels.setPixelColor(pos -2, bright/5, 0, bright/5);
    pixels.setPixelColor(pos -1, bright/2, 0, bright/2);
    pixels.setPixelColor(pos, bright, 0, bright);
    pixels.setPixelColor(pos +1, bright/2, 0, bright/2);
    pixels.setPixelColor(pos +2, bright/5, 0, bright/5);
    pixels.setPixelColor(pos +3, bright/13, 0, bright/13);
    pixels.setPixelColor(pos +4, bright/20, 0, bright/20);

    // actually show the pixel image we've just defined
    pixels.show();

    // move LED image on step in direction dir
    pos+=dir;

    // if we've gone below position 0, reverse direction
    if(pos < -2) {
      digitalWrite(syncPin,HIGH);
      //delay(0);
      digitalWrite(syncPin,LOW);
      pos = -1;
      dir = -dir;
    }
    // if we've gone above position 8, reverse direction
    else if(pos > 9) {
      digitalWrite(syncPin,HIGH);
      delayMicroseconds(1000);
      digitalWrite(syncPin,LOW);
      pos = 8;
      dir = -dir;
    }  
  }

  // sleep for a while (time modulated by right poti)
  delayMicroseconds(wait);

  if(wait > 1024*8) {
    wait = 0;
  }
}

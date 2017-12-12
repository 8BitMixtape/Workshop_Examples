#include "neolib.h"

// hardware description / pin connections
#define SPEAKERPIN      1
#define NEOPIXELPIN     0

// fast pin access
#define AUDIOPIN (1<<SPEAKERPIN)
#define PINLOW (PORTB&=~AUDIOPIN)
#define PINHIGH (PORTB|=AUDIOPIN)

int pos = 0; // current position of larson scanner
int dir = 1; // direction in which we're moving
int bright = 255; // max. brightness
int wait = 70; // scanner speed

int snd = 0; 
long t = 0; 
uint16_t p1 = 2;

void setup() 
{
  neobegin();
  pinMode(SPEAKERPIN, OUTPUT);
}

void loop() 
{
  // generate our sound output
  uint16_t valuePoti = analogRead(POTI_RIGHT);
  p1 = 1023 - valuePoti>>5;
  snd = (t|3) * ((t>>1|t>>6)&p1&t>>3);
  digitalWrite (SPEAKERPIN, snd);
  t++;
  delayMicroseconds(wait);

  // update LEDs every 150 sound-cycles
  if (t % 150 == 0) {

    setColorAllPixel  ( COLOR_BLACK ); // clear all pixels
    
    bright = map (getPoti( POTI_RIGHT ), 0, 1023, 10, 255); // map brightness to left poti
    wait = map (getPoti( POTI_LEFT ), 0, 1023, 300, 0); // map speed to right poti
  
    pixels.setPixelColor(pos -4, bright/20, 0, bright/20);
    pixels.setPixelColor(pos -3, bright/13, 0, bright/13);
    pixels.setPixelColor(pos -2, bright/5, 0, bright/5);
    pixels.setPixelColor(pos -1, bright/2, 0, bright/2);
    pixels.setPixelColor(pos, bright, 0, bright);
    pixels.setPixelColor(pos +1, bright/2, 0, bright/2);
    pixels.setPixelColor(pos +2, bright/5, 0, bright/5);
    pixels.setPixelColor(pos +3, bright/13, 0, bright/13);
    pixels.setPixelColor(pos +4, bright/20, 0, bright/20);
    pixels.show();
  
  
  //  delay(wait); 
  
    pos+=dir;
    if(pos < -2) {
      pos = -1;
      dir = -dir;
    }
    else if(pos > 9) {
      pos = 8;
      dir = -dir;
    }  
  }
}


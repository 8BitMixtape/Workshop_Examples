/*
CV GATE random generator
*/

#include "neolib.h"

#define TRIGGER  PB5
#define CV      PB1

#define NOTE_AB4 207.652
#define NOTE_A4  220.000
#define NOTE_AS4 233.082
#define NOTE_BB4 NOTE_As
#define NOTE_B4  246.942
#define NOTE_C4  261.626
#define NOTE_CS4 277.183
#define NOTE_DB4 NOTE_Cs
#define NOTE_D4  293.665
#define NOTE_DS4 311.127
#define NOTE_EB4 NOTE_Ds
#define NOTE_E4  329.628
#define NOTE_F4  349.228
#define NOTE_FS4 369.994
#define NOTE_GB4 NOTE_Fs
#define NOTE_G4  391.995
#define NOTE_GS4 415.305

#define NOTE_REST     0.0
#define NOTE_SUSTAIN -1.0


int tempo = 150;

int notes_length = 0;

#define NUM_COMPOSITION 36
/*
float composition[] = {
    NOTE_D, NOTE_E, NOTE_F, NOTE_G, NOTE_A*2, NOTE_As*2,
    NOTE_Db, NOTE_As*2, NOTE_A*2, NOTE_G, NOTE_F, NOTE_E,
    NOTE_F, NOTE_REST, NOTE_A*2, NOTE_REST, NOTE_D*2, NOTE_REST,
    NOTE_G, NOTE_REST, NOTE_Cs*2, NOTE_REST, NOTE_E*2, NOTE_REST,

    NOTE_D*2, NOTE_E*2, NOTE_F*2, NOTE_G*2, NOTE_A*4, NOTE_As*4,
    NOTE_Db*2, NOTE_As*4, NOTE_A*4, NOTE_G*2, NOTE_F*2, NOTE_E*2,
};

*/

typedef struct {
  int note;
  int tempo;
} notesType;



const notesType aNotes[] = {
    // 1
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 125}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_GS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 125}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_GS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_G4, 250}, {NOTE_GS4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 125}, {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_FS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 250}, {NOTE_GS4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 125}, {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_FS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    // 2
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 125}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_GS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 125}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_GS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_G4, 250}, {NOTE_GS4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 125}, {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_FS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 250}, {NOTE_GS4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 125}, {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_FS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    // 3
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 125}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_GS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, 
    {NOTE_A4, 125}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_GS4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, {NOTE_A4, 125}, 
    {NOTE_G4, 250}, {NOTE_GS4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 125}, {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_FS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 250}, {NOTE_GS4, 125}, {NOTE_G4, 125}, 
    {NOTE_G4, 125}, {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_GS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    {NOTE_FS4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, {NOTE_G4, 125}, 
    // solo 
    
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_E4*2, 1500}, 
    {NOTE_A4*2, 250}, {NOTE_AS4*2, 125}, {NOTE_A4*2, 125}, {NOTE_E4*2, 1500}, 
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_E4*2, 250}, {NOTE_A4*2, 250}, {NOTE_G4*2, 2000}, 
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_E4*2, 1500}, 
    {NOTE_A4*2, 250}, {NOTE_AS4*2, 125}, {NOTE_A4*2, 125}, {NOTE_E4*2, 1500}, 
    {NOTE_A4, 250}, {NOTE_AS4, 125}, {NOTE_A4, 125}, {NOTE_E4*2, 250}, {NOTE_A4*2, 250}, {NOTE_AS4*2, 2500}, {NOTE_G4*2, 250}, {NOTE_A4*2, 500}
    
};



void setup(){
  neobegin();
  pinMode(TRIGGER, OUTPUT);
  pinMode(CV, OUTPUT);

  notes_length = sizeof(aNotes)/sizeof(aNotes[0]);

}  


unsigned int i = 0;


void loop(){
  uint16_t lp = getPoti( POTI_LEFT );   // range 0..1023
  //uint16_t rp = getPoti( POTI_RIGHT );  // range 0..1023

  static uint16_t i = 0;
  i++;



  digitalWrite(TRIGGER, HIGH);
  //delay(lp*random(1,3));
  //delay(lp);
  analogWrite(CV, aNotes[i%notes_length].note);
  delay(aNotes[i%notes_length].tempo);
  digitalWrite(TRIGGER, LOW);
  //delay(lp*random(1,2));
  //delay(lp);

/*
  unsigned long note = aNotes[i++].note;
    if (i >= (sizeof aNotes / sizeof *aNotes)) {
        digitalWrite(TRIGGER, LOW);
        delay(1000);
        i = 0;
        return;
    }
    if (note == NOTE_REST)
        digitalWrite(TRIGGER, LOW);
    else if (note == NOTE_SUSTAIN)
        ;      // Don't do anything, just let the current tone continue
    else
        digitalWrite(TRIGGER, HIGH);
        analogWrite(CV, note);
    // If we want space between the notes, pass tempo as a third arg
    // to tone(), then do noTone() afterward.

    delay(tempo);
*/

/*
    pixels.setPixelColor(0,COLOR_RED);
  pixels.setPixelColor(1,COLOR_ORANGE);
  pixels.setPixelColor(2,COLOR_YELLOW);
  pixels.setPixelColor(3,COLOR_LIGHTGREEN);
  pixels.setPixelColor(4,COLOR_GREEN);
  pixels.setPixelColor(5,COLOR_DARKGREEN);
  pixels.setPixelColor(6,COLOR_BLUE);
  pixels.setPixelColor(7,COLOR_DARKBLUE);
  
  pixels.show();                      // This sends the updated pixel color to the hardware.
  delay(50);                        

  pixels.setPixelColor(0,COLOR_BLACK);
  pixels.setPixelColor(1,COLOR_WHITE);
  pixels.setPixelColor(2,COLOR_GRAY);
  pixels.setPixelColor(3,COLOR_BROWN);
  pixels.setPixelColor(4,COLOR_TURQUOISE);
  pixels.setPixelColor(5,COLOR_CYAN);
  pixels.setPixelColor(6,COLOR_PINK);
  pixels.setPixelColor(7,COLOR_BLACK);

  pixels.show();                      // This sends the updated pixel color to the hardware.
  delay(50);    
  */
}

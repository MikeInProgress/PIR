#include "pitches.h"
#define PIR 2
#define Buzzer A5

#define LED_R 7

#define SEG_C 11
#define SEG_E 9
#define SEG_D 10
#define SEG_B 13
#define SEG_G 6
#define SEG_A 12
#define SEG_F 8
int melody[] = {

  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,//18
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST,4, NOTE_AS4,4,  

  NOTE_D5, 2, NOTE_AS4, 4,//26
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
};


int tempo = 115;
int wholenote = (60000 * 4) / tempo;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int divider = 0, noteDuration = 0,Number = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  
  pinMode(PIR,INPUT);
  pinMode(Buzzer,OUTPUT);
  pinMode(LED_R,OUTPUT);
  digitalWrite(LED_R, LOW);

  attachInterrupt(digitalPinToInterrupt(PIR), alarm, RISING);
}
void figure(int cyfra) {
  //Instrukcja switch ustawia odpowiednie stany na wyjsciach
  //w zaleznosci od podanej cyfry
  switch (cyfra) {
    case 0:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, LOW);
    break; 
    
    case 1:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break; 
    
    case 2:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
    break; 
    
    case 3:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
    break; 
    
    case 4:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
    break; 
    
    case 5:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
    break; 
    
    case 6:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
    break;
   
    case 7:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
    break;
    
    case 8:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
    break;
    
    case 9:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        
    break;
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(PIR) == LOW)
  {
    digitalWrite(LED_R, LOW);
    noTone(Buzzer);
  }else
  {
    digitalWrite(LED_R, HIGH);
     for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }

    tone(Buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);   
      }
    }
    }

    
   void alarm() {
  
  figure(Number);
  Number++; 
}
   
  

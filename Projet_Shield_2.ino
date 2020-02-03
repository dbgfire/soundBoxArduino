#include "Midi.h"

#define MAX_PISTE 3
#define MAX_NOTE 100
#define MAX_INSTRUMENT 100

#define PIN_BUTTON_1 5
#define PIN_BUTTON_2 4
#define PIN_BUTTON_3 3

#define PIN_POTAR_NOTE A8
#define PIN_POTAR_VITESSE A9
#define PIN_POTAR_INSTRUMENT A10

#define PIN_BUTTON_SWITCH 6
#define PIN_BUTTON_ENRENGISTREMENT 7


int indexPiste = 0;
int indexNote[3];
int indexInstrument[3];

int button1State = LOW;
int button2State = LOW;
int button3State = LOW;
int buttonSwitchState = LOW;
int buttonEnrengistrementState = LOW;

int matrixVitesse[MAX_PISTE][MAX_NOTE];
int matrixNote[MAX_PISTE][MAX_NOTE];
int matrixInstrument[MAX_PISTE][MAX_INSTRUMENT];

bool inputButton1 = false;
bool toogle1 = false;
bool inputButton2 = false;
bool toogle2 = false;
bool inputButton3 = false;
bool toogle3 = false;
bool inputButtonSwitch = false;
bool toogleSwitch = false;
bool inputButtonEnrengistrement = false;
bool toogleEnrengistrement = false;


unsigned long time_for_action_1 = 1000000000;
unsigned long time_for_action_2 = 1000000000;
unsigned long time_for_action_3 = 1000000000;

int i = 0;
int j = 0;

void setup() {
  Serial.begin(9600);
  player.beginInMidiFmt();
  for(i=0; i<MAX_PISTE; i++){
    for(j=0; j<MAX_NOTE; j++){
      matrixVitesse[i][j] = 3000;
      matrixNote[i][j] = 100;
    }
  }
  for(i=0; i<MAX_PISTE; i++){
    for(j=0; j<MAX_INSTRUMENT; j++){
      matrixInstrument[i][j] = 10;
    }
  }
  for(i=0; i<MAX_PISTE; i++){  
    indexNote[i] = 0;
    indexInstrument[i] = 0;
  }
  
  pinMode(PIN_BUTTON_1, INPUT);
  pinMode(PIN_BUTTON_2, INPUT);
  pinMode(PIN_BUTTON_3, INPUT);
  pinMode(PIN_BUTTON_SWITCH, INPUT);
  pinMode(PIN_BUTTON_ENRENGISTREMENT, INPUT);

}



void loop() {

//=====================================================
//Gestion bouton
  button1State = digitalRead(PIN_BUTTON_1);
  button2State = digitalRead(PIN_BUTTON_2);
  button3State = digitalRead(PIN_BUTTON_3);
  buttonSwitchState = digitalRead(PIN_BUTTON_SWITCH);
  buttonEnrengistrementState = digitalRead(PIN_BUTTON_ENRENGISTREMENT);

  if(buttonSwitchState == HIGH){
    inputButtonSwitch = true;
  }
  if(inputButtonSwitch == true && buttonSwitchState == LOW){
    inputButtonSwitch = false;
    indexPiste++;
    if(indexPiste >= MAX_PISTE){
      indexPiste = 0;
    }
    Serial.println("----------------");
    Serial.print("Switch piste: ");
    Serial.println(indexPiste);
  }
    
  if(button1State == HIGH){
    inputButton1 = true;
  }
  if(inputButton1 == true && button1State == LOW){
    inputButton1 = false;
    if(toogle1){
      Serial.println("----------------");
      Serial.print("Piste 1: ");
      toogle1 = false;
      time_for_action_1 = 1000000000;
      Serial.println(toogle1);
    }else{
      Serial.println("----------------");
      Serial.print("Piste 1: ");
      toogle1 = true;
      time_for_action_1 = 0;
      Serial.println(toogle1);
    }
  }
  
  if(button2State == HIGH){
    inputButton2 = true;
  }
  if(inputButton2 == true && button2State == LOW){
    inputButton2 = false;
    if(toogle2){
      Serial.println("----------------");
      Serial.print("Piste 2: ");
      toogle2 = false;
      time_for_action_2 = 1000000000;
      Serial.println(toogle2);
    }else{
      Serial.println("----------------");
      Serial.print("Piste 2: ");
      toogle2 = true;
      time_for_action_2 = 0;
      Serial.println(toogle2);
    }
  }
  
  if(button3State == HIGH){
    inputButton3 = true;
  }
  if(inputButton3 == true && button3State == LOW){
    inputButton3 = false;
    if(toogle3){
      Serial.println("----------------");
      Serial.print("Piste 3: ");
      toogle3 = false;
      time_for_action_3 = 1000000000;
      Serial.println(toogle3);
    }else{
      Serial.println("----------------");
      Serial.print("Piste 3: ");
      toogle3 = true;
      time_for_action_3 = 0;
      Serial.println(toogle3);
    }
  }
  
  if(buttonEnrengistrementState == HIGH){
    inputButtonEnrengistrement = true;
  }
  if(inputButtonEnrengistrement == true && buttonEnrengistrementState == LOW){
    inputButtonEnrengistrement = false;
    if(toogleEnrengistrement){
      Serial.println("----------------");
      Serial.println("Enrengistrement OFF");
      toogleEnrengistrement = false;
    }else{
      toogleEnrengistrement = true;
      Serial.println("----------------");
      Serial.println("Enrengistrement ON");
    }
  }

//=====================================================
//Gestion potar

  if(toogleEnrengistrement){
    matrixNote[indexPiste][indexNote[indexPiste]] = map(analogRead(PIN_POTAR_NOTE), 0, 1023, 1, 127);
    matrixVitesse[indexPiste][indexNote[indexPiste]] = map(analogRead(PIN_POTAR_VITESSE), 0, 1023, 500, 2000);
    matrixInstrument[indexPiste][indexInstrument[indexPiste]] = map(analogRead(PIN_POTAR_INSTRUMENT), 0, 1023, 1, 127);
/*
    Serial.println("------------------------");
    Serial.print("indexPiste:");
    Serial.println(indexPiste);
    Serial.print("indexNote:");
    Serial.println(indexNote[indexPiste]);
    Serial.print("Note:");
    Serial.println(matrixNote[indexPiste][indexNote[indexPiste]]);
    Serial.print("Vitesse:");
    Serial.println(matrixVitesse[indexPiste][indexNote[indexPiste]]);
    Serial.print("Instrument:");
    Serial.println(matrixInstrument[indexPiste][indexInstrument[indexPiste]]);
    Serial.println("------------------------");
*/
  }

//=====================================================
//Gestion piste
  if (millis() > time_for_action_1) {
    for(i=0; i<128;i++)
      midiNoteOff(0, i,0);
    time_for_action_1 = millis() + matrixVitesse[0][indexNote[0]];
    Serial.println(time_for_action_1);
    midiWriteData(0xC0, matrixInstrument[0][indexInstrument[0]], 0);
    midiNoteOn(0, matrixNote[0][indexNote[0]],127);
    Serial.print("indexNote: ");
    Serial.println(indexNote[0]);
    Serial.print("note: ");
    Serial.println(matrixNote[0][indexNote[0]]);

    indexNote[0]++;
    if(indexNote[0] >= MAX_NOTE){
      indexNote[0] = 0;
    }
    indexInstrument[0]++;
    if(indexInstrument[0] >= MAX_INSTRUMENT){
      indexInstrument[0] = 0;
    }
  }
  
  if (millis() > time_for_action_2) {
    for(i=0; i<128;i++)
      midiNoteOff(1, i,0);
    time_for_action_2 = millis() + matrixVitesse[1][indexNote[1]];
    Serial.println(time_for_action_2);
    midiWriteData(0xC0, matrixInstrument[1][indexInstrument[1]], 0);
    midiNoteOn(1, matrixNote[1][indexNote[1]],127);
    Serial.print("indexNote: ");
    Serial.println(indexNote[1]);
    Serial.print("note: ");
    Serial.println(matrixNote[1][indexNote[1]]);

    indexNote[1]++;
    if(indexNote[1] >= MAX_NOTE){
      indexNote[1] = 0;
    }
    indexInstrument[1]++;
    if(indexInstrument[1] >= MAX_INSTRUMENT){
      indexInstrument[1] = 0;
    }
  }


  if (millis() > time_for_action_3) {
    for(i=0; i<128;i++)
      midiNoteOff(2, i,0);
    time_for_action_3 = millis() + matrixVitesse[2][indexNote[2]];
    Serial.println(time_for_action_2);
    midiWriteData(0xC0, matrixInstrument[2][indexInstrument[2]], 0);
    midiNoteOn(2, matrixNote[2][indexNote[2]],127);
    Serial.print("indexNote: ");
    Serial.println(indexNote[2]);
    Serial.print("note: ");
    Serial.println(matrixNote[2][indexNote[2]]);

    indexNote[2]++;
    if(indexNote[2] >= MAX_NOTE){
      indexNote[2] = 0;
    }
    indexInstrument[2]++;
    if(indexInstrument[2] >= MAX_INSTRUMENT){
      indexInstrument[2] = 0;
    }
  }
//  delay(1000);
}

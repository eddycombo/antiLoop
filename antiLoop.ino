#include <SoftwareSerial.h>
#include <MIDI.h>

SoftwareSerial stageSerial(2,3);
SoftwareSerial backstageSerial(4, 5);

byte previousCtlChange;
byte previousCtlVal;

unsigned long resetTime;

MIDI_CREATE_INSTANCE(SoftwareSerial, stageSerial,     stage); 
MIDI_CREATE_INSTANCE(SoftwareSerial, backstageSerial, backstage);

void setup(){

  stage.begin(16);
  previousCtlChange = 0; // previous controller num
}

void loop(){
  //read midi input from stage [midiparse]
  if (stage.read()){

    //check if controller num == previous controller num [zl compare]

    if(stage.getData1() != previousCtlChange){

      //if different passes to stage output  and reset Timer [select 0 1] [timer]

      stage.send(stage.getType(), stage.getData1(), stage.getData2(), stage.getChannel());
      resetTimer();
      previousCtlChange = stage.getData1();  
  }
    else{

      //if same control num as previous [select 0 1]

      //check if time since last message is > 100;

      if(millis() - resetTime > 100){
        //true passes to midiout A
        stage.send(stage.getType(), stage.getData1(), stage.getData2(), stage.getChannel());              
      }
      resetTimer();
      previousCtlChange = stage.getData1();
    }
  }
}

void resetTimer(){

  resetTime = millis();

}


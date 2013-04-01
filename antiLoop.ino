#include <SoftwareSerial.h>
#include <MIDI.h>
#define  ledPin 4

SoftwareSerial midi1Serial(2,3);
//SoftwareSerial midi2Serial(5,6);


byte currentChannelMidi1;
byte currentCtlMidi1;
byte currentCtlValMidi1;
byte previousCtlMidi1;
byte previousCtlValMidi1;


byte currentChannelMidi2;
byte currentCtlMidi2;
byte currentCtlValMidi2;
byte previousCtlMidi2;
byte previousCtlValMidi2;

unsigned long resetTime;
unsigned long resetTime2;

MIDI_CREATE_INSTANCE(SoftwareSerial, midi1Serial,     midi1); 
//MIDI_CREATE_INSTANCE(SoftwareSerial, midi2Serial,     midi2);

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midi2);

void setup(){

  midi1.begin(16);
  midi1.turnThruOff();
  
  midi2.begin(16);
  midi2.turnThruOff();
  
  Serial.begin(9600);
  
  previousCtlMidi1 = 0;
  previousCtlValMidi1 = 0; // previous controller num
  
  previousCtlMidi2 = 0;
  previousCtlValMidi2 = 0;
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop(){
  

  //midi1
  if (midi1.read()){

   if(midi1.getType() == midi::ControlChange){ 
     
     
     currentChannelMidi1 = midi1.getChannel();
     currentCtlMidi1 = midi1.getData1();
     currentCtlValMidi1 = midi1.getData2();
     
    
     
     if(currentCtlMidi1 == previousCtlMidi1 && currentCtlValMidi1 == previousCtlValMidi1){
       
       resetTimer();
       
       while(millis() - resetTime < 100){
       } 
       
       midi2.send(midi::ControlChange, currentCtlMidi1, currentCtlValMidi1, currentChannelMidi1);
           
      
    }else{

     
      //if different passes to stage output  and reset Timer [select 0 1] [timer]
      resetTimer();
      midi2.send(midi::ControlChange, currentCtlMidi1, currentCtlValMidi1, currentChannelMidi1);
     }
        previousCtlMidi1 = currentCtlMidi1;
        previousCtlValMidi1 = currentCtlValMidi1;  
      }
  }
  
  
  ///// midi2
  if (midi2.read()){

   if(midi2.getType() == midi::ControlChange){ 
     
     
     currentChannelMidi2 = midi2.getChannel();
     currentCtlMidi2 = midi2.getData1();
     currentCtlValMidi2 = midi2.getData2();
     
    
     
     if(currentCtlMidi2 == previousCtlMidi2 && currentCtlValMidi2 == previousCtlValMidi2){
       
       resetTimer2();
       
       while(millis() - resetTime2 < 100){
       } 
       
       midi1.send(midi::ControlChange, currentCtlMidi2, currentCtlValMidi2, currentChannelMidi2);
           
      
    }else{

     
      //if different passes to stage output  and reset Timer [select 0 1] [timer]
      resetTimer2();
      midi1.send(midi::ControlChange, currentCtlMidi2, currentCtlValMidi2, currentChannelMidi2);
     }
        previousCtlMidi2 = currentCtlMidi2;
        previousCtlValMidi2 = currentCtlValMidi2;  
      }
  }
  
}

void resetTimer(){

  resetTime = millis();

}

void resetTimer2(){

  resetTime2 = millis();

}


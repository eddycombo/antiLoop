#include <SoftwareSerial.h>
#define  ledPin 4

SoftwareSerial midi1Serial(2,3);
//SoftwareSerial midi2Serial(5,6);


byte in1_Message[3];
byte in2_Message[3];

byte prevIn1_Message[3];
byte prevIn2_Message[3];

int inRead1, inRead2;

unsigned long lastTimeMidi1;
unsigned long lastTimeMidi2;
unsigned long currentTimeMidi1;
unsigned long currentTimeMidi2;

unsigned long midiLoopTime;

void setup(){

  midi1Serial.begin(31250);
  Serial.begin(31250);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  lastTimeMidi1 = millis();
  lastTimeMidi2 = millis();
  
  midiLoopTime = 50;
}

void loop(){
  
  ////MIDI INPUT 1
  if(midi1Serial.available()>0){
    
    if(inRead1 < 3){
      in1_Message[inRead1] = midi1Serial.read();
      inRead1 ++;
    }
    
    if(inRead1 >=3){
     inRead1 = 0;
    
        ///if CC ou PC
          if(in1_Message[0] == 191){
 
       //get time of message
       currentTimeMidi1 = millis();
     
       //check against previous message type AND timing
       if(in1_Message[1] == prevIn1_Message[1] && in1_Message[2] == prevIn1_Message[2] && currentTimeMidi1 - lastTimeMidi1 < midiLoopTime){
     
       ///MIDI LOOP : DO NOTING
     
         }else{
     
             for(int i = 0; i<3; i++){
    
                Serial.write(in1_Message[i]);
             }
         }
           prevIn1_Message[0] = in1_Message[0];
           prevIn1_Message[1] = in1_Message[1];
           prevIn1_Message[2] = in1_Message[2];
           lastTimeMidi1 = currentTimeMidi1;
       }
    }
  }

  ////MIDI INPUT 2
  if(Serial.available()>0){
    
    if(inRead2 < 3){
      in2_Message[inRead2] = Serial.read();
      inRead2 ++;
    }
    
    if(inRead2 >=3){
     inRead2 = 0;
    
        ///if CC
          if(in2_Message[0] == 191){
   
       //get time of message
       currentTimeMidi2 = millis();
     
       //check against previous message type AND timing
       if(in2_Message[1] == prevIn2_Message[1] && in2_Message[2] == prevIn2_Message[2] && currentTimeMidi2 - lastTimeMidi2 < midiLoopTime){
     
       ///MIDI LOOP : DO NOTING
     
         }else{
     
             for(int i = 0; i<3; i++){
    
                midi1Serial.write(in2_Message[i]);
             }
         }
           prevIn2_Message[0] = in2_Message[0];
           prevIn2_Message[1] = in2_Message[1];
           prevIn2_Message[2] = in2_Message[2];
           lastTimeMidi2 = currentTimeMidi2;
       }
    }
  }
} 
 
    
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


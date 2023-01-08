#include <RF24.h>

//Set up NRF module
RF24 radio(9, 10); // CE, CSN

//Set up address of communication (Must be the same for both transmitter and reciever)
const byte address[6] = "01931";    //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

//Initialize and define pins
const int step1 = 2;
const int dir1 = 5;
const int step2 = 4;
const int dir2 = 7;
int relayPin = 3;

boolean button_state = 0;
int input;
char remoteInput[32] = "";  

void setup() {
  //Set all pins to output
  pinMode(step1,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(step2,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  //Set up radio communication. This begins creates a form of communication at the address determined above then starts listening
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();
}

//Main loop code
void loop() {
  //Ask if there is data being recieved. If there is then read and continue accordingly
  if(radio.available()){
    radio.read(&remoteInput, sizeof(remoteInput));
    Serial.println(remoteInput);
 
    //If the input is "shoot" then switch the trigger relay on and off
    if(strcmp(remoteInput,"shoot") == 0){
      digitalWrite(relayPin, HIGH);
      delay(125);
      digitalWrite(relayPin, LOW);
    }

    //If the input is "left" then run the motors to turn left (Counterclockwise)
    if(strcmp(remoteInput,"left") == 0){
      digitalWrite(dir1,HIGH);
      for(int x = 1; x<=100; x++){
        digitalWrite(step1,HIGH);
        //digitalWrite(step2,HIGH);
        delayMicroseconds(500);
        digitalWrite(step1,LOW);
        //digitalWrite(step2,LOW);  
        delayMicroseconds(500);
        }
      }
      //If the input is "right" then run the motors to turn right (Clockwise)
      else if(strcmp(remoteInput,"right") == 0){
        digitalWrite(dir1,LOW);    
        for(int x = 1; x<=100; x++){
          digitalWrite(step1,HIGH);
          //digitalWrite(step2,HIGH);
          delayMicroseconds(500);
          digitalWrite(step1,LOW);
          //digitalWrite(step2,LOW);  
          delayMicroseconds(500);
        }
      }
      //If the input is "up" then run the motors to turn up
      if(strcmp(remoteInput,"up") == 0){
        digitalWrite(dir2,HIGH);
        for(int x = 1; x<=50; x++){
          digitalWrite(step2,HIGH);
          delayMicroseconds(750);
          digitalWrite(step2,LOW);  
          delayMicroseconds(750);
        }
      }
      //If the input is "down" then run the motors to turn down
      else if(strcmp(remoteInput,"down") == 0){
        digitalWrite(dir2,LOW);    
        for(int x = 1; x<=50; x++){
          digitalWrite(step2,HIGH);
          delayMicroseconds(750);
          digitalWrite(step2,LOW);  
          delayMicroseconds(750);
        }
      } 
  }
}

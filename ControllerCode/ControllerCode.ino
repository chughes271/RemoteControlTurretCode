#include <EducationShield.h>
#include <RF24.h>

//Set up NRF module
RF24 radio(9, 10); // CE, CSN         
//Set up Joystick
Joystick joystick = Joystick(A0,A1); // X, Y

//Set up address of communication (Must be the same for both transmitter and reciever)
const byte address[6] = "01931";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

//Set up pins and variables for the button and joystick
int button_pin = 2;
int joystickPitch;
int joystickYaw;

boolean button_state = 0;
char output;


void setup() {
  //Set button pin as an input
  pinMode(button_pin, INPUT);
  
  //Set up radio communication. This begins creates a form of communication at the address determined above then starts writing
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

//Main loop code
void loop(){
  //Read all possible inputs from button and joystick
  button_state = digitalRead(button_pin);
  joystickPitch= joystick.getX();
  joystickYaw= joystick.getY();
  
  //If button is pressed then write "shoot" 
  if(button_state == HIGH){
    output = "shoot";
    radio.write(&output, sizeof(output));                  //Sending the message to receiver
  }

//Joystick X

  //If joystick is moved up then write "up"
  if(joystickPitch == 1){
    output = "up";
    radio.write(&output, sizeof(output));                  //Sending the message to receiver 
  }
  //If joystick is moved down then write "down"
  else if(joystickPitch == -1){
    output = "down";
    radio.write(&output, sizeof(output));                  //Sending the message to receiver 
  }

//Joystick Y

  //If joystick is moved right then write "right" (Clockwise)
  if(joystickYaw == 1){
    output = "right";
    radio.write(&output, sizeof(output));                  //Sending the message to receiver 
  }
  //If joystick is moved left then write "left" (Counterclockwise)
  else if(joystickYaw == -1){
    output = "left";
    radio.write(&output, sizeof(output));                  //Sending the message to receiver 
  }
  
  delay(100);
}

#include <Arduino.h>
#include <CayenneMQTTSerial.h>

int topLimit = 2; //limit switches
int bottomLimit = 3;

int leftHBridge = 4;
int rightHBridge = 5;

int state = 1; 

/*
state = 0 :stop
state = 1 :bottomLimit switch
state = 2 :topLimit switch
state = 3 :bridge going up
state = 4 :bridge going down
*/

int channel1 = 0; //values returned by virtual channels
int channel2 = 0;

char username[] = " "; //Cayenne username
char password[] = " "; //password
char clientID[] = " "; //clientID

#define VIRTUAL_CHANNEL_1 1 //selected virtual channels
#define VIRTUAL_CHANNEL_2 2


void stopMotor(){
  digitalWrite(leftHBridge,HIGH);
  digitalWrite(rightHBridge,HIGH);
  
}

void upMotor(){
  state = 3;
  digitalWrite(leftHBridge,HIGH);
  digitalWrite(rightHBridge,LOW);
}

void downMotor(){
  state = 4;
  digitalWrite(leftHBridge,LOW);
  digitalWrite(rightHBridge,HIGH);
}

void topDetect(){
  state = 2;
  stopMotor();
}

void bottomDetect(){
  state = 1;
  stopMotor();
}

void setup()
{
  pinMode(topEindLoop,INPUT_PULLUP);
  pinMode(bottomEindLoop,INPUT_PULLUP);
  pinMode(leftHBridge,OUTPUT);
  pinMode(rightHBridge,OUTPUT);
  Cayenne.begin(username, password, clientID,9600);
}

void loop() {
  Cayenne.loop();
	
  if(digitalRead(bottomEindLoop)==1 && state == 4){
  
    bottomDetect();
    
  } 
  if(digitalRead(topEindLoop)==1 && state == 3){

    topDetect();
  }  
    if(channel1 == 1 && (state == 1 || state == 4)){
    if(channel1 !=channel2){
      upMotor();
    }
  }
    if(channel2 == 1 &&(state ==2 ||state == 3)){
    if(channel1 !=channel2){
      downMotor();
    }
  }
}


CAYENNE_IN(VIRTUAL_CHANNEL_1) //reading virtualchannel 1
{
	int value = getValue.asInt();
	CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNEL_1, value);
  channel1=value;

}

CAYENNE_IN(VIRTUAL_CHANNEL_2) //reading virtualchannel 2
{
	int value = getValue.asInt();
	CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNEL_2, value);
  channel2=value;
}

CAYENNE_OUT_DEFAULT() //keeping cayenne awake
{
	Cayenne.virtualWrite(0, millis());
}


CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
}

#include <Arduino.h>
#include <CayenneMQTTSerial.h>

int topEindLoop = 2;
int bottomEindLoop = 3;

int leftHBridge = 4;
int rightHBridge = 5;

int incomingByte = 0;

int state = 1;
int channel1 = 0;
int channel2 = 0;

char username[] = "e0abbbc0-b0d0-11ec-a681-73c9540e1265";
char password[] = "2d5434e6253fd493bb519a9a0627b1464ef40c4f";
char clientID[] = "552484c0-d1c2-11ec-a681-73c9540e1265";
#define VIRTUAL_CHANNEL_1 1
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


CAYENNE_IN(VIRTUAL_CHANNEL_1)
{
	int value = getValue.asInt();
	CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNEL_1, value);
  channel1=value;

}

CAYENNE_IN(VIRTUAL_CHANNEL_2)
{
	int value = getValue.asInt();
	CAYENNE_LOG("Channel %d, pin %d, value %d", VIRTUAL_CHANNEL_2, value);
  channel2=value;
}

CAYENNE_OUT_DEFAULT()
{
	Cayenne.virtualWrite(0, millis());
}


CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
}
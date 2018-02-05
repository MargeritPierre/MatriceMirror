#include <AccelStepper.h>

int motorStepPin1 = 2;
int motorDirPin1 = 3;

int motorStepPin2 = 4;
int motorDirPin2 = 5;

int motorStepPin3 = 6;
int motorDirPin3 = 7;

int motorStepPin4 = 8;
int motorDirPin4 = 9;

int motorStepPin5 = 10;
int motorDirPin5 = 11;

int motorStepPin6 = 12;
int motorDirPin6 = 13;

long Pos[7] = {0,0,0,0,0,0,0};
//long i = 0;
//long time = 0;
//long duree = 0;

AccelStepper stepper1 (AccelStepper::DRIVER, motorStepPin1, motorDirPin1); 
AccelStepper stepper2 (AccelStepper::DRIVER, motorStepPin2, motorDirPin2);
AccelStepper stepper3 (AccelStepper::DRIVER, motorStepPin3, motorDirPin3);
AccelStepper stepper4 (AccelStepper::DRIVER, motorStepPin4, motorDirPin4);
AccelStepper stepper5 (AccelStepper::DRIVER, motorStepPin5, motorDirPin5);
AccelStepper stepper6 (AccelStepper::DRIVER, motorStepPin6, motorDirPin6);

void setup()
{  
  initSerial();
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  
  mode(0,1); // setting microstepping mode
  mode(1,1);
  mode(2,0);
  
  // Change these to suit your stepper if you want
  stepper1.setMaxSpeed(10000);
  stepper1.setAcceleration(10000);
  stepper2.setMaxSpeed(10000);
  stepper2.setAcceleration(10000);
  stepper3.setMaxSpeed(10000);
  stepper3.setAcceleration(10000);
  stepper4.setMaxSpeed(10000);
  stepper4.setAcceleration(10000);
  stepper5.setMaxSpeed(10000);
  stepper5.setAcceleration(10000);
  stepper6.setMaxSpeed(10000);
  stepper6.setAcceleration(10000);
}

void setzero(int id)
{
  if (id == 1) {
stepper1.setCurrentPosition(0);
stepper2.setCurrentPosition(0);
  }
  if (id == 2) {
stepper3.setCurrentPosition(0);
stepper4.setCurrentPosition(0);
  }
  if (id == 2) {
stepper5.setCurrentPosition(0);
stepper6.setCurrentPosition(0);
  }
//Serial.print ("SetZero ");
//Serial.println(id);
}


void loop()
{ 
//  i = i+1;
//  if (i % 100000 == 0)
//  {
//  duree = (micros() - time)/100000;
//  Serial.print("duree : ");
//  Serial.println(duree);
//  time = micros();
//  }
  processSerial();
  //Follow_Path(stepper1.currentPosition(), stepper2.currentPosition());
  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();
  stepper5.run();
  stepper6.run();
}

void moveTo(int idStepper, int pos)
{
  //Serial.print(pos); 
   switch (idStepper) 
    {
      case 1 :
        stepper1.moveTo(pos); 
        break;
      case 2 :
        stepper2.moveTo(pos); 
        break;
      case 3 :
        stepper3.moveTo(pos); 
        break;
      case 4 :
        stepper4.moveTo(pos); 
        break;
      case 5 :
        stepper5.moveTo(pos); 
        break;
      case 6 :
        stepper6.moveTo(pos); 
        break;
    }
  //Serial.print(" ");
}

void setSpeed(int idStepper, int speed)
{
  //Serial.print ("speed ");
  //Serial.println(speed);
  stepper1.setMaxSpeed(10000);
  stepper2.setMaxSpeed(10000);
  stepper3.setMaxSpeed(10000);
  stepper4.setMaxSpeed(10000);
  stepper5.setMaxSpeed(10000);
  stepper6.setMaxSpeed(10000);
}

void setAcc(int idStepper, int acc)
{
  //Serial.print ("acc ");
  //Serial.println(acc);
  stepper1.setAcceleration(10000);
  stepper2.setAcceleration(10000);
  stepper3.setAcceleration(10000);
  stepper4.setAcceleration(10000);
  stepper5.setAcceleration(10000);
  stepper6.setAcceleration(10000);
}

void fastStop(int idStepper){
  //Serial.println("stop");
  if (idStepper == 1) {
  stepper1.stop();
  }
  if (idStepper == 2) {
  stepper2.stop();
  }
}

void reverse(int idStepper, int i)
{
  switch (idStepper) 
    {
      case 1 :
        stepper1.setPinsInverted(i,0,0); 
        break;
      case 2 :
        stepper2.setPinsInverted(i,0,0); 
        break;
      case 3 :
        stepper3.setPinsInverted(i,0,0); 
        break;
      case 4 :
        stepper4.setPinsInverted(i,0,0); 
        break;
      case 5 :
        stepper5.setPinsInverted(i,0,0); 
        break;
      case 6 :
        stepper6.setPinsInverted(i,0,0); 
        break;
    }
    //Serial.print("Reverse "); 
    //Serial.println(idStepper);
}

void mode(int idStepper, int i)
{
  switch (idStepper) 
    {
      case 0 :
        if (i==1) digitalWrite(A3,HIGH);
        else digitalWrite(A3,LOW);  
        break;
      case 1 :
        if (i==1) digitalWrite(A4,HIGH);
        else digitalWrite(A4,LOW);  
        break;
      case 2 :
        if (i==1) digitalWrite(A5,HIGH);
        else digitalWrite(A5,LOW); 
        break;
    }
}

void set(int idStepper, int pos)
{
  switch (idStepper) 
    {
      case 1 :
        stepper1.setCurrentPosition(pos);  
        break;
      case 2 :
        stepper2.setCurrentPosition(pos);  
        break;
      case 3 :
        stepper3.setCurrentPosition(pos);  
        break;
      case 4 :
        stepper4.setCurrentPosition(pos);  
        break;
      case 5 :
        stepper5.setCurrentPosition(pos);  
        break;
      case 6 :
        stepper6.setCurrentPosition(pos);  
        break;
    }
}

//long currentX()
//{
//  return stepper1.currentPosition();
//}
//
//long currentY()
//{
//  return stepper2.currentPosition();
//}



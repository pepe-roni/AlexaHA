Servo servoFS;
Servo servoEA;

void setup() 
{
    servoFS.attach(D0);
    servoEA.attach(D1);
}

void loop() 
{
    servoFS.write(180);
    servoEA.write(0);
}
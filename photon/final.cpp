// This #include statement was automatically added by the Particle IDE.
#include "RelayShield/RelayShield.h"

RelayShield myRelays; 

void setup()
{
    myRelays.begin();
    Particle.function("getWater", getWaterHandler);
    Particle.function("getWater2", getWaterTwoHandler);
    //IFTTT relay control
    Particle.function("relayOne", relayOneHandler);
    Particle.function("relayTwo", relayTwoHandler);
    Particle.function("relayThree", relayThreeHandler);
    Particle.function("relayFour", relayFourHandler);
    Particle.function("allRelays", allRelaysHandler);
}

void loop()
{
    delay(250)
}


int relayOneHandler(String args)
{
    if(myRelays.isOn(1))
    {
        myRelays.off(1);
        delay(100);
        return 0;
    }
    else
    {
        myRelays.on(1);
        delay(100);
        return 1;
    }
}

int relayTwoHandler(String args){
    
    if(myRelays.isOn(2))
    {
        myRelays.off(2);
        delay(100);
        return 0;
    }
    else
    {
        myRelays.on(2);
        delay(100);
        return 1;
    }
}

int relayThreeHandler(String args){
    if(myRelays.isOn(3))
    {
        myRelays.off(3);
        delay(100);
        return 0;
    }
    else
    {
        myRelays.on(3);
        delay(100);
        return 1;
    }
}

int relayFourHandler(String args){
    if(myRelays.isOn(4))
    {
        myRelays.off(4);
        delay(100);
        return 0;
    }
    else
    {
        myRelays.on(4);
        delay(100);
        return 1;
    }
}

int allRelaysHandler(String args){
    for(int i=1; i<5; i++)
    {
        if(myRelays.isOn(i))
        {
            myRelays.off(i);
            delay(100);
            return 0;
        }
        else
        {
            myRelays.on(i);
            delay(50);
            return 1;
        }
    }
    return -1;
 
}

int getWaterHandler(String args)
{
    int soilM = analogRead(0);
    String callback = args; 
    if(callback == "error")
    {
        return -1;
    }
    else
        return soilM; 
}

int getWaterTwoHandler(String args)
{
    String callback = args;
    int soilSensorTwo = analogRead(1);
    if(callback == "error")
    {
        return -1;
    }
    else
        return soilSensorTwo;
}
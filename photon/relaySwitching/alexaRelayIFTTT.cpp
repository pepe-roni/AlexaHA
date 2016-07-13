// This #include statement was automatically added by the Particle IDE.
#include "RelayShield/RelayShield.h"

// Create an instance of the RelayShield library, so we have something to talk to
RelayShield myRelays;

void setup() {
    // .begin() sets up a couple of things and is necessary to use the rest of the functions
    //max 4 subscriptions
    myRelays.begin();
    Particle.subscribe("allRelays", allRelaysHandler, MY_DEVICES);
    Particle.subscribe("relayOne", relayOneHandler, MY_DEVICES);
    Particle.subscribe("relayTwo", relayTwoHandler, MY_DEVICES);
    Particle.subscribe("relayThree", relayThreeHandler, MY_DEVICES);
    Particle.subscribe("relayFour", relayFourHandler, MY_DEVICES);
    // Use myRelays.begin(2); if you have the square, white RelayShield (from the Core)
    // to use, just add a '2' between the parentheses in the code above.
}

void loop() 
{
    delay(100);
    
}

void relayOneHandler(String event, String data)
{
    if(myRelays.isOn(1))
    {
        myRelays.off(1);
        delay(100);
    }
    else
    {
    myRelays.on(1);
    delay(100);
    }
}

void relayTwoHandler(String event, String data)
{
    
    if(myRelays.isOn(2))
    {
        myRelays.off(2);
        delay(100);
    }
    else
    {
    myRelays.on(2);
    delay(100);
    }
}

void relayThreeHandler(String event, String data)
{
    if(myRelays.isOn(3))
    {
        myRelays.off(3);
        delay(100);
    }
    else
    {
    myRelays.on(3);
    delay(100);
    }
}

void relayFourHandler(String event, String data)
{
    if(myRelays.isOn(4))
    {
        myRelays.off(4);
        delay(100);
    }
    else
    {
    myRelays.on(4);
    delay(100);
    }
}

void allRelaysHandler(String event, String data)
{

    for(int i=1; i<5; i++)
    {
        if(myRelays.isOn(i))
        {
            myRelays.off(i);
            delay(100);
        }
        else
        {
            myRelays.on(i);
        delay(50);
        }
    }
 
}
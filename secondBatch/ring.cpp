#include "Particle.h"

int buttonState;

void setup()
{
    Particle.variable("bs", buttonState);
    pinMode(D1,INPUT_PULLUP);
    pinMode(D2, OUTPUT);
}

void loop() 
{
    buttonState = digitalRead(D1);
    
    if(buttonState == 1){
        WiFi.off();
         wifiLEDHandler();
    }
    else
    {
        WiFi.on();
        delay(7500);
        wifiLEDHandler();
        Particle.publish("bell rung");
        delay(7500);
    }
}

bool wifiLEDHandler()
{
    bool wifiReady = WiFi.ready();
    if(wifiReady){
         digitalWrite(D2, HIGH);
         return true;
    }
    else
    {
        digitalWrite(D2,LOW);
        return false;
    }
}

#include "Particle.h"

int buttonState;
bool forceWiFi = false;

void setup()
{
    Particle.variable("bs", buttonState);
    pinMode(D1,INPUT_PULLUP);
    //button at D1 tracked with buttonstate 
    pinMode(D2, OUTPUT);
    //led at D2 shows wifi module connection and 
    //therefore ensures succesful event publish
    pinMode(D3, INPUT_PULLUP);
    attachInterrupt(D3, interruptHandler, CHANGE);
    //an interrupt that runs interruptHandler when D3 is high
    //can be accomplished with a wire to GND or a button.
}

void loop() 
{
    buttonState = digitalRead(D1);
    if(!forceWiFi)
    {
        if(buttonState == 1){
            WiFi.off();
            //turns wifi module off when nothing is happening
            //since buttonstate is 1, there is no data that needs to be transmitted
            wifiLEDHandler();
        }
        else
        {
            WiFi.on();
            //turns wifi module on when the event, being buttonstate !1 is true
            //delay allows for adequate time for wifi connection 
            delay(3000);
            wifiLEDHandler();
            //publishes an event for IFTTT to listen
            Particle.publish("bell");
            //Longer delay times allows for the ellimination of erraneous and extra calls to publish
            delay(8500);
        }
    }
    else 
    {
        WiFi.on();
        delay(3500);
        wifiLEDHandler();
    }
}


//this function checks if the wifi module has successful established a 
//connection to the cloud, an LED at D2 turns on if it has been established and 
//published an event within 3500ms-~3700ms
//the return functionality is for debugging 
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


//failsafe or for when developing
//useful for turning on the wifi to flash code
void interruptHandler()
{
    if(wifiLEDHandler())
    {
        forceWiFi = false;
    }
    else
    forceWiFi = true;
}

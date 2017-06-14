#include "Particle.h"

int buttonState;

void setup()
{
    Particle.variable("bs", buttonState);
    pinMode(D1,INPUT_PULLUP);
}

void loop()
{
    buttonState = digitalRead(D1);

}

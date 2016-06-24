// This #include statement was automatically added by the Particle IDE.
#include "RelayShield/RelayShield.h"

// Create an instance of the RelayShield library, so we have something to talk to
RelayShield myRelays;

void setup() {
    // .begin() sets up a couple of things and is necessary to use the rest of the functions
    myRelays.begin();

    // Use myRelays.begin(2); if you have the square, white RelayShield (from the Core)
    // to use, just add a '2' between the parentheses in the code above.
}

void loop() {
    // If relay1 is on, then turn it off
    
    
    if(myRelays.isOn(1)){    // myRelays.isOn(1) will return TRUE if relay 1 on and FALSE if it's off
        myRelays.off(1);     // myRelays.off(#) will switch relay # off
    }
    
    // If it wasn't already on, then turn it on
    else{
        myRelays.on(1);      // myRelays.on(#) will switch relay # on
    }
    
    // Change it once a second
    delay(1000);
}
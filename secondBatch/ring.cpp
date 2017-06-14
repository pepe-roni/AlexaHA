#include "Particle.h"

unsigned long firstAvailable = 0;
int buttonState;

void setup()
{
    Particle.variable("bs", buttonState);
    pinMode(D1,INPUT_PULLUP);
}

void loop()
{
    buttonState = digitalRead(D1);
    bool wifiReady = WiFi.ready();
	bool cloudReady = Particle.connected();
	if (wifiReady) {
		if (firstAvailable == 0) {
			firstAvailable = millis();
		}
		if (millis() - firstAvailable > 30000) {
			// After we've been up for 30 seconds, go to sleep
			Serial.println("calling System.sleep(30)");
			System.sleep(30);

			// This happens immediately - System.sleep(30) doesn't block and your code keeps running, just with
			// Wi-Fi and cloud turned off. The LED should breathe white instead of cyan in this state. Then,
			// after the time expires, reconnection to the cloud occurs
			Serial.println("returned from sleep");
		}
	}
	else {
		firstAvailable = 0;
	}
}

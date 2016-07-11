double resistance; 
#define SERIES_RESISTOR     560    // Value of the series resistor in ohms.    
#define SENSOR_PIN          5      // Analog pin which is connected to the sensor. 
#define ZERO_VOLUME_RESISTANCE    0.00    // Resistance value (in ohms) when no liquid is present.
#define CALIBRATION_RESISTANCE    0.00    // Resistance value (in ohms) when liquid is at max line.
#define CALIBRATION_VOLUME        0.00    // Volume (in any units) when liquid is at max line.

void setup() 
{
    Particle.variable("resistance",resistance);
}

void loop()
{
    int pin = SENSOR_PIN;
    int seriesResistance = SERIES_RESISTOR;
   double resistance = analogRead(pin);
  // Convert ADC reading to resistance.
  resistance = (1023.0 / resistance) - 1.0;
  resistance = seriesResistance / resistance;
delay(1000);
}

double readResistance(int pin, int seriesResistance) {
  // Get ADC value.
  double resistance = analogRead(pin);
  // Convert ADC reading to resistance.
  resistance = (1023.0 / resistance) - 1.0;
  resistance = seriesResistance / resistance;
  return resistance;
}

double resistanceToVolume(float resistance, float zeroResistance, float calResistance, float calVolume) {
  if (resistance > zeroResistance || (zeroResistance - calResistance) == 0.0) {
    // Stop if the value is above the zero threshold, or no max resistance is set (would be divide by zero).
    return 0.0;
  }
  // Compute scale factor by mapping resistance to 0...1.0+ range relative to maxResistance value.
  double scale = (zeroResistance - resistance) / (zeroResistance - calResistance);
  // Scale maxVolume based on computed scale factor.
  return calVolume * scale;
}
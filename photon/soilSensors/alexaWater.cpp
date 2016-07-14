
void setup()
{
    Particle.function("getWater", getWaterHandler);
    Particle.function("getWater2", getWaterTwoHandler);
}

void loop()
{
    delay(250);
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

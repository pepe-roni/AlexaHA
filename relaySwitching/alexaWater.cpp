
void setup()
{
    Particle.function("levels", levels);
}

void loop()
{
    delay(500);
}

int levels(String args)
{
    int soilSensor = analogRead(0);
    int soilSensorTwo = analogRead(1);
    int callIndex = args.indexOf(',');
    String call = args.substring(0,callIndex);
    
    if(call == "one")
    {
        return(soilSensor);
    }
    else if(call == "two")
    {
        return(soilSensorTwo);
    }
    else
    {
        return -1; 
    }
}
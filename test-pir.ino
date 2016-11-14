// Variables
int PIRpin = D1;
int LED = D7;                       // Integrated LED location
int PIRstate = LOW;                 // we start, assuming no motion detected
int PIRvalue = 0;                   // variable for reading the pin status
int PIRcalibrateTime = 10000;       // wait for the thingy to calibrate

void setup() {
    pinMode(LED, OUTPUT);       // declare integrated blue LED as output
    pinMode(PIRpin, INPUT);     // declare PIR sensor as input
}

void loop()
{
  // if the sensor is calibrated
  if ( PIRcalibrated() )
  {
    // get the data from the sensor
    readTheSensor();

    // report it out, if the state has changed
    reportTheData();
  }
}

void readTheSensor() {
  PIRvalue = digitalRead(PIRpin);
}

bool PIRcalibrated() {
  return millis() - PIRcalibrateTime > 0;
}

void reportTheData() {

  // if the sensor reads high
  // or there is now motion
  if (PIRvalue == HIGH) {

    // the current state is no motion
    // i.e. it's just changed
    // announce this change by publishing an event
    if (PIRstate == LOW) {
      // we have just turned on
      Particle.publish("Motion","Movement detected");
      // Update the current state
      PIRstate = HIGH;
      setLED( PIRstate );
    }
  } else {
    if (PIRstate == HIGH) {
      // we have just turned of
      // Update the current state
      PIRstate = LOW;
      setLED( PIRstate );
    }
  }
}

void setLED( int state )
{
  digitalWrite( LED, state );
}
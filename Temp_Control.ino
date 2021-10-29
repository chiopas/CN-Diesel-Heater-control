#include <DallasTemperature.h>
#include <OneWire.h>

// The cable of the Dallas sensor on Arduino pin 2
#define ONE_WIRE_BUS 2

// Sets a oneWire instance to communicate with any OneWire device (not just Maxim / Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Let's pass our oneWire source to the Dallas sensor.
DallasTemperature sensors(&oneWire);

int relay = 11; // pin for relay - active = high;
int relay2 = 7; // pin for relay2 - active = high;

void setup(void)
{
  // Initialize serial communication
  Serial.begin(9600);
  
  pinMode (relay, OUTPUT); // relay pin set to output
  pinMode (relay2, OUTPUT); // relay2 pin set to output 
  // Let's start the library
  sensors.begin();
}
void loop(void)
{
   // call the sensors.requestTemperatures () function to show global temperature
   // request to all devices on the bus
  Serial.print("Reading temperature...");
  sensors.requestTemperatures(); // send the value request
  
  if(sensors.getTempCByIndex(0) >= 23){
    digitalWrite (relay2, HIGH); // energize the relay
    Serial.print("Turn off!");
    delay(1000);
    digitalWrite (relay2, LOW); // relay is off
  }
  if(sensors.getTempCByIndex(0) <= 20
  ){
    digitalWrite (relay, HIGH); // energize the relay
    Serial.print("Turn on!");
    delay(1000);
    digitalWrite (relay, LOW); // relay is off
  }
  
  Serial.print("The temperature is:");  // show the temperature on the serial screen
  Serial.println(sensors.getTempCByIndex(0));
  delay(300000);
}

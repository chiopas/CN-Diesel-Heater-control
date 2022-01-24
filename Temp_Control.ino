#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal.h>

// The cable of the Dallas sensor on Arduino pin 2
#define ONE_WIRE_BUS 6

// Sets a oneWire instance to communicate with any OneWire device (not just Maxim / Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int state = 0;
float temp;
int ontemp = 20;
int offtemp = 22;
// Let's pass our oneWire source to the Dallas sensor.
DallasTemperature sensors(&oneWire);

int relay = 7; // pin for relay - active = high;


void setup(void)
{
  // Initialize serial communication
  Serial.begin(9600);
  lcd.begin(16, 2);  
  pinMode (relay, OUTPUT); // relay pin set to output
  // Let's start the library
  sensors.begin();
}
  void turnoff() {
    digitalWrite (relay, HIGH); // energize the relay
    lcd.clear();
    lcd.print("Turn off!");
    delay(5000);
    digitalWrite (relay, LOW); // relay is off
    delay(5000);
    state = 0;
    delay(1000);
  }

  void turnon(){
     digitalWrite (relay, HIGH); // energize the relay
     lcd.setCursor(0,1);
     lcd.print("Turn on!");
     delay(1000);
     digitalWrite (relay, LOW); // relay is off
     delay(5000);
     state = 1;
     delay(1000);
    }
void loop()
{
   // call the sensors.requestTemperatures () function to show global temperature
   // request to all devices on the bus
  sensors.requestTemperatures(); // send the value request
  float temp = sensors.getTempCByIndex(0);
    
  if(temp > offtemp && state == 0 || temp > offtemp + 1 && state == 1){
  lcd.setCursor(0,1);
  lcd.print("Already off");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Temperature:");  // show the temperature on the serial screen
  lcd.println(temp);
  delay(1000);
  }
  else if(temp > offtemp && state == 1) {
  turnoff();
  }
  
  if(temp < ontemp && state == 1 || temp < ontemp - 2 && state == 0){
  lcd.setCursor(0,1);
  lcd.print("Already on");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Temperature:");  // show the temperature on the serial screen
  lcd.println(temp);
  delay(1000);
  }
  
  else if (temp < ontemp && state == 0){
  turnon();
  }
  
  if (temp < offtemp && temp > ontemp){
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print(" ");
  }  

}

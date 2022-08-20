/*
 * Project pumpkinScaleCode
 * Description:
 * Author:
 * Date:
 */

#include "HX711.h"
HX711 myScale (D13,D2); // any two digital pins

float CAL_FACTOR =1700; // changing value changes get_units units (lb , g, ton , etc .)
const int SAMPLES =10; // number of data points averaged when using get_units or get_value

float weight, rawData ,calibration ;
int offset;
  
void setup () {
Serial.begin(9600);
Serial.println("HX711 calibration sketch");
Serial.println("Remove all weight from scale");
Serial.println("After readings begin, place known weight on scale");
Serial.println("Press + or a to increase calibration factor");
Serial.println("Press - or z to decrease calibration factor");

myScale.set_scale (); // initialize loadcell
delay (3000) ; // let the loadcell settle
myScale.tare (); // set the tare weight (or zero )

long zero_factor = myScale.read_average(); //Get a baseline reading
Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
Serial.println(zero_factor);
}

void loop () {
myScale.set_scale (CAL_FACTOR); // adjust when calibrating scale to desired units
// Using data from loadcell
Serial.print("Reading: ");
weight = myScale.get_units (SAMPLES); // return weight in units set by set_scale ();
Serial.printf("weight %f \n",weight);
delay (3000); // add a short wait between readings

if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      CAL_FACTOR += 10;
    else if(temp == '-' || temp == 'z')
      CAL_FACTOR -= 10;
  }

// Other useful HX711 methods
rawData = myScale.get_value (SAMPLES);// returns raw loadcell reading minus offset
offset = myScale.get_offset (); // returns the offset set by tare ();
calibration = myScale.get_scale (); // returns the cal_factor used by set_scale ();
}


  // Infineon RGB_LED_Shield_Master_Tester
  // by Michelle Chia

  // Demonstrates I2C communication with the RGB LED Shield for safe configuration. Tested at 48Vin, 6V forward voltage LED. LED current up to 350mA.
  // Modified 13 August 2014 
  
 
  
  #include <Wire.h>
  #include "Infineon.h"

  
  Infineon RGBLEDS = Infineon();

  int rval = 0;
  int gval = 0;
  int bval = 0;
 void setup() {                

    Serial.begin(9600);
    Wire.begin();
    
    while (RGBLEDS.on != 1) // Wait for shield to respond, keep setting the values till it does
    {
      RGBLEDS.I2CWRITE2BYTES (ADDRESS, FADERATE, 0x0000); // Immediate fade
      RGBLEDS.I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0000); // 0% brightness level
      RGBLEDS.on = RGBLEDS.I2CREAD(ADDRESS, READ_DIMMINGLEVEL); // Request for brightness level
      if (RGBLEDS.message == 1 && RGBLEDS.on == 0) // If message received and dimming level = 0%, "message" is set in the I2CREAD function
      {
        RGBLEDS.message = 0;
        RGBLEDS.on = 1; // break out of loop
      }
    }
    
    RGBLEDS.I2CWRITE2BYTES (ADDRESS, OFFTIME_RED, 0x38); // Set off-time of red channel to 0x38
    RGBLEDS.I2CWRITE2BYTES (ADDRESS, OFFTIME_GREEN, 0x39); // Set off-time of green channel to 0x39
    RGBLEDS.I2CWRITE2BYTES (ADDRESS, OFFTIME_BLUE, 0x38); // Set off-time of blue channel to 0x38
    RGBLEDS.I2CWRITE6BYTES (ADDRESS, CURRENT_RGB, 0x80, 0x80, 0x80); // Set current of red channel to 0x80 = 780mA
    RGBLEDS.I2CWRITE2BYTES (ADDRESS, FADERATE, 0x0000); // Fade Rate between intensities --> 0.0s
    RGBLEDS.I2CWRITE2BYTES (ADDRESS, WALKTIME, 0x0000); // walk time between colors = 0s
    RGBLEDS.I2CWRITE6BYTES (ADDRESS, INTENSITY_RGB, 0x0555, 0x0555, 0x0555); // low level White Light
    RGBLEDS.I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0FFF); // Maximum dimming level means inensity settings are directly used


}
  
  // the loop routine runs over and over again forever:
  void loop() {

   while(Serial.available()>0)
   {
    rval = Serial.parseInt();
    gval=Serial.parseInt();
    bval=Serial.parseInt();

    rval = map(rval,0,255,0,4095);
    gval = map(gval,0,255,0,4095);
    bval = map(bval,0,255,0,4095);
   
     RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, rval, gval, bval);
     delay(1);
   
   }
    // change lamp colour to red
   /* RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0x0, 0x0); // all off
    delay(500); // wait 1000ms
    // change lamp colour to green
   // RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 4095, 4095, 4095); // 25%
   // delay(500); 
    // change lamp colour to blue
    RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 4095, 0, 0); // Blue
    delay(500);
    RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0, 4095, 0); // Blue
    delay(500);
    RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0, 0, 4095); // Blue
    delay(500);

    RGBLEDS.I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 4095, 4095, 4095); // Blue
    delay(500);
  }  */
  Serial.flush();
  }
 



 

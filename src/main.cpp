/*

Pimoroni i2c Dual Matrices Example.

*/


// pull in the Arduino framework.
#include <Arduino.h>



// pull in the Pimoroni i2c Dual Matrices driver.
#include <PimoroniDualMatrice.h>

// set our i2c board address
#define PIMORONIDUALMATRICEI2CADDRESS 0x61

// mydualmatrice is the local driver object.
PimoroniDualMatrice mydualmatrice;











/// @brief Set up the chip..
void setup() {

  // set up the chip one time on startup.

  // tell the driver to connect to the chip, at the right address, and turn it on.  
  mydualmatrice.begin( PIMORONIDUALMATRICEI2CADDRESS );

  // that's all for setup.

}










uint8_t xpos = 0;

uint8_t ypos = 0;




/// @brief Arduino framework main loop. update the display with a new number on each matrix.
void loop() {

  // clear the old screen off
  mydualmatrice.clear();

  // first, lets move in a random direction.

  if ( (uint8_t)( random( 2 ) ) ) {
    if ( xpos != 9 ) {
      xpos++;
    }
  }
  else {
    if ( xpos != 0 ) {
      xpos--;
    }
  }

  if ( (uint8_t)( random( 2 ) ) ) {
    if ( ypos != 6 ) {
      ypos++;
    }
  }
  else {
    if ( ypos != 0 ) {
      ypos--;
    }
  }

  // now setpixel this location...

  if ( xpos < 5 ) {
    mydualmatrice.pixelSet( 0 , xpos , ypos , 1 );
  }
  else {
    mydualmatrice.pixelSet( 1 , xpos - 5 , ypos , 1 );
  }







  
  // tell the chip to update the display, and show the new numbers.
  mydualmatrice.updateDisplay();
   
  // now wait a while
  delay( 250 );

  // and go around again.
  return;

}



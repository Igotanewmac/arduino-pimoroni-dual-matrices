/*

Pimoroni i2c Dual Matrices Example.

This example demonstrates the fill method.

This example shows a pair of binary counters.  Each row is a binary digit.  0 for off, 1 for on.
The left matrix is counting up, the right matrix is counting down.

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









/// @brief Arduino framework main loop. update the display with a new number on each matrix.
void loop() {

  // clear the old screen off
  mydualmatrice.clearAll();

  // count from 0 to 0b10000000
  for ( uint8_t x = 0 ; x < 0b10000000 ; x++ ) {

    // write the current number to the left matrix.
    mydualmatrice.fill( 0 , x );

    // write the inverse of the current number to the right matrix.
    mydualmatrice.fill( 1 , ~x );

    // tell the chip to update the display.
    mydualmatrice.updateDisplay();

    // wait a while
    delay( 100 );

    // now go around again for the next iteration of x.

  }


  // show the end result for a second.
  delay( 1000 );


  // blank the screen for the end.
  mydualmatrice.clearAll();

  // tell the chip to update the display.
  mydualmatrice.updateDisplay();
   
  // now wait a while
  delay( 1000 );

  // and go around again.
  return;

}



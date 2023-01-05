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
  mydualmatrice.clear( 0 );
  mydualmatrice.clear( 1 );


  for ( uint8_t x = 0 ; x < 0b10000000 ; x++ ) {

    mydualmatrice.fill( 0 , x );
    mydualmatrice.fill( 1 , ~x );

    mydualmatrice.updateDisplay();

    delay( 100 );


  }


  // blank the screen for the end.
  mydualmatrice.clear( 0 );
  mydualmatrice.clear( 1 );

  // tell the chip to update the display, and show the new pixel.
  mydualmatrice.updateDisplay();
   
  // now wait a while
  delay( 1000 );

  // and go around again.
  return;

}



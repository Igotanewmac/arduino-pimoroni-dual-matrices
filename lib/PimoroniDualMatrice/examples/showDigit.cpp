/*

Pimoroni i2c Dual Matrices Example.

This example demonstrates the showDigit method.

This example shows two counters.
The left matrix will count up.  The right matrix will count down.

*/


// pull in the Arduino framework.
#include <Arduino.h>



// pull in the Pimoroni i2c Dual Matrices driver.
#include <PimoroniDualMatrice.h>

// set our i2c board address
#define PIMORONIDUALMATRICEI2CADDRESS 0x61

// mydualmatrice is the local driver object.
PimoroniDualMatrice mydualmatrice;











/// @brief Set up the chip.
void setup() {

  // set up the chip one time on startup.

  // tell the driver to connect to the chip, at the right address, and turn it on.  
  mydualmatrice.begin( PIMORONIDUALMATRICEI2CADDRESS );

  // that's all for setup.

}












/// @brief A counter for the display digit.
uint8_t x = 0;


/// @brief Arduino framework main loop. update the display with a new number on each matrix.
void loop() {

  // show an increasing counter on the left matrix.
  mydualmatrice.showDigit( 0 , x );
  
  // show a decreasing counter on the right matrix.
  mydualmatrice.showDigit( 1 , 15 - x );
  
  // tell the chip to update the display, and show the new numbers.
  mydualmatrice.updateDisplay();
  
  // increase the counter for the next loop.
  x++;

  // if the counter is 16 ...
  if ( x == 0x10 ) {
    // ... then reset it to zero.
    x = 0;
  }
  
  // now wait a while
  delay( 500 );

  // and go around again.
  return;

}



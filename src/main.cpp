/*

Pimoroni i2c Dual Matrices Example.

This example shows a dot chasing around on the matrices.

This example demonstrates the pixelSet method.

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









/// @brief The pixel x position.
uint8_t xpos = 0;

/// @brief The pixel y position.
uint8_t ypos = 0;




/// @brief Move in a relative direction, without running off the edge of the matrices.
/// @param xposrelative The step to take in the xpos direction. -1 , 0 , 1.
/// @param yposrelative The step to take in the ypos direction. -1 , 0 , 1.
void moveSafelyTo( int8_t xposrelative , int8_t yposrelative ) {

  // bounds check for xpos
  switch (xposrelative) {

    case -1: // step left
      // check we are not already at minimum.
      if ( xpos != 0 ) {
        // if not at minimum, move left.
        xpos--;
      }
      // all done, skip the rest.
      break;
    
    case  0: // no step
      // nothing to do, so skip everything.
      break;
    
    case  1: // step right
      // check we are not already at maximum.
      if ( xpos != 9 ) {
        // if not, move right.
        xpos++;
      }
      // all done, skip the rest.
      break;
    
  }

  // bounds check for ypos
  switch (yposrelative) {

    case -1: // step up
    // check we are not already at the minimum.
      if ( ypos != 0 ) {
        // if not, move up.
        ypos--;
      }
      // all done, skip the rest.
      break;
    
    case  0: // no step
      // nothing to do, so skip everything.
      break;
    
    case  1: // step down
      // check we are not already at maximum.
      if ( ypos != 6 ) {
        // if not, move down.
        ypos++;
      }
      // all done, skip the rest.
      break;
    
  }


  // all done, return to caller.
  return;

}






/// @brief Arduino framework main loop. update the display with a new number on each matrix.
void loop() {

  // clear the old screen off
  mydualmatrice.clear( 0 );
  mydualmatrice.clear( 1 );

  // move the pixel in a random direction.
  moveSafelyTo( random( -1 , 2 ) , random( -1 , 2 ) );

  // now turn on the pixel at this location...

  // check to see which matrix the pixel is on.
  if ( xpos < 5 ) {
    // if xpos is below 5, it's the left matrix.
    mydualmatrice.pixelSet( 0 , xpos , ypos , 1 );
  }
  else {
    // if xpos is above 5, it's the right matrix.
    mydualmatrice.pixelSet( 1 , xpos - 5 , ypos , 1 );
  }

  // tell the chip to update the display, and show the new pixel.
  mydualmatrice.updateDisplay();
   
  // now wait a while
  delay( 100 );

  // and go around again.
  return;

}



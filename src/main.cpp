#include <Arduino.h>

// pull in my library.
#include <PimoroniDualMatrice.h>


#ifndef wire
#include <Wire.h>
#define wire Wire
#endif




PimoroniDualMatrice mydualmatrice;

#define PIMORONIDUALMATRICEI2CADDRESS 0x61




uint8_t xposlb = 0;
uint8_t yposlb = 0;
uint8_t xposrb = 4;
uint8_t yposrb = 4;






void setup() {
  // put your setup code here, to run once:
  
  
  mydualmatrice.begin( PIMORONIDUALMATRICEI2CADDRESS );


  mydualmatrice.updateDisplay();


}

void loop() {
  // put your main code here, to run repeatedly:


  // turn off the old pixel
  mydualmatrice.pixelSet( 0 , xposlb , yposlb , 0 );

  // move on....
  xposlb++;
  
  if ( xposlb == 5 ) {
    yposlb++;
    xposlb = 0;
  }

  if ( yposlb == 7 ) {
    yposlb = 0;
  }

  // now set the new pixel on...
  mydualmatrice.pixelSet( 0 , xposlb , yposlb , 1 );

  


  // turn off the old pixel
  mydualmatrice.pixelSet( 1 , xposrb - 1 , yposrb , 0 );

  // move on....
  xposrb--;
  
  if ( xposrb == 0 ) {
    yposrb++;
    xposrb = 6;
  }

  if ( yposrb == 7 ) {
    yposrb = 0;
  }

  // now set the new pixel on...
  mydualmatrice.pixelSet( 1 , xposrb - 1 , yposrb , 1 );

  
  
  
  
  mydualmatrice.updateDisplay();

  // now wait a while
  delay( 50 );

  // and go around again.
  return;

}



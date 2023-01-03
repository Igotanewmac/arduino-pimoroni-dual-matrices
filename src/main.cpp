#include <Arduino.h>

// pull in my library.
#include <PimoroniDualMatrice.h>


#ifndef wire
#include <Wire.h>
#define wire Wire
#endif




PimoroniDualMatrice mydualmatrice;

#define PIMORONIDUALMATRICEI2CADDRESS 0x61











void setup() {
  // put your setup code here, to run once:
  
  
  mydualmatrice.begin( PIMORONIDUALMATRICEI2CADDRESS );


  mydualmatrice.updateDisplay();


}



uint8_t x = 0;

void loop() {
  // put your main code here, to run repeatedly:


  mydualmatrice.showDigit( 0 , x );
  
  mydualmatrice.showDigit( 1 , x );
  
  x++;

  if ( x == 0x10 ) {
    x = 0;
  }
  
  mydualmatrice.updateDisplay();

  // now wait a while
  delay( 500 );

  // and go around again.
  return;

}



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
  
  
  /*
  wire.begin();
  */

  /*
  // config register
  wire.beginTransmission( 0x61 );
  wire.write( 0x00 );
  wire.write( 0b00011000 );
  wire.endTransmission();
  */

  /*
  // lighting effect register
  wire.beginTransmission( 0x61 );
  wire.write( 0x0D );
  wire.write( 0b00000110 );
  wire.endTransmission();
  */

  /*
  // pwm register
  wire.beginTransmission( 0x61 );
  wire.write( 0x19 );
  wire.write( 32 );
  wire.endTransmission();
  */

  // set bank one on
  wire.beginTransmission( 0x61 );
  wire.write( 0x01 );
  //            ...54321 <x>
  wire.write( 0b11100000 ); // 1 y 
  wire.write( 0b11100110 ); // 2
  wire.write( 0b11100100 ); // 3
  wire.write( 0b11100100 ); // 4
  wire.write( 0b11100100 ); // 5
  wire.write( 0b11101110 ); // 6
  wire.write( 0b01100000 ); // 7
  wire.endTransmission();
  
  
  
  // set bank two on
  wire.beginTransmission( 0x61 );
  wire.write( 0x0E );
  //            .7654321 <y>
  wire.write( 0b10000000 ); // 1 x
  wire.write( 0b10100010 ); // 2
  wire.write( 0b10110010 ); // 3
  wire.write( 0b10101100 ); // 4
  wire.write( 0b10000000 ); // 5
  wire.write( 0b11111111 ); // 6
  wire.write( 0b11111111 ); // 7
  wire.write( 0b10111111 ); // 8
  wire.endTransmission();
  

  
  /*
  // column update register
  wire.beginTransmission( 0x61 );
  wire.write( 0x0C );
  wire.write( 0b00000000 );
  wire.endTransmission();
  */

  mydualmatrice.updateDisplay();


}

void loop() {
  // put your main code here, to run repeatedly:
}



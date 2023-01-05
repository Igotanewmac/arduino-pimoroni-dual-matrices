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






/// @brief A three character wide pixel buffer!
uint8_t mypixelbuffer[15] = { 0 };










void loadDigitIntoPixelBuffer( uint8_t digit ) {

  uint8_t tempbytes[5] = { 0 };

  tempbytes[ 0 ] = mydualmatrice.columnGet( 0 , 0 );
  tempbytes[ 1 ] = mydualmatrice.columnGet( 0 , 1 );
  tempbytes[ 2 ] = mydualmatrice.columnGet( 0 , 2 );
  tempbytes[ 3 ] = mydualmatrice.columnGet( 0 , 3 );
  tempbytes[ 4 ] = mydualmatrice.columnGet( 0 , 4 );
  
  mydualmatrice.showDigit( 0 , digit );

  // copy out goes here
  mypixelbuffer[ 10 ] = mydualmatrice.columnGet( 0 , 0 );
  mypixelbuffer[ 11 ] = mydualmatrice.columnGet( 0 , 1 );
  mypixelbuffer[ 12 ] = mydualmatrice.columnGet( 0 , 2 );
  mypixelbuffer[ 13 ] = mydualmatrice.columnGet( 0 , 3 );
  mypixelbuffer[ 14 ] = mydualmatrice.columnGet( 0 , 4 );


  // now put everything back where it belongs
  mydualmatrice.columnSet( 0 , 1 , tempbytes[ 0 ] );
  mydualmatrice.columnSet( 1 , 1 , tempbytes[ 1 ] );
  mydualmatrice.columnSet( 2 , 1 , tempbytes[ 2 ] );
  mydualmatrice.columnSet( 3 , 1 , tempbytes[ 3 ] );
  mydualmatrice.columnSet( 4 , 1 , tempbytes[ 4 ] );
  
  // now all done, return to caller.
  return;
}




void doscroll() {
  mypixelbuffer[ 0  ] = mypixelbuffer[ 1  ];
  mypixelbuffer[ 1  ] = mypixelbuffer[ 2  ];
  mypixelbuffer[ 2  ] = mypixelbuffer[ 3  ];
  mypixelbuffer[ 3  ] = mypixelbuffer[ 4  ];
  mypixelbuffer[ 4  ] = mypixelbuffer[ 5  ];
  mypixelbuffer[ 5  ] = mypixelbuffer[ 6  ];
  mypixelbuffer[ 6  ] = mypixelbuffer[ 7  ];
  mypixelbuffer[ 7  ] = mypixelbuffer[ 8  ];
  mypixelbuffer[ 8  ] = mypixelbuffer[ 9  ];
  mypixelbuffer[ 9  ] = mypixelbuffer[ 10 ];
  mypixelbuffer[ 10 ] = mypixelbuffer[ 11 ];
  mypixelbuffer[ 11 ] = mypixelbuffer[ 12 ];
  mypixelbuffer[ 12 ] = mypixelbuffer[ 13 ];
  mypixelbuffer[ 13 ] = mypixelbuffer[ 14 ];
  mypixelbuffer[ 14 ] = 0x00;
  return;
}





void sendtochip() {

  mydualmatrice.columnSet( 0 , 0 , mypixelbuffer[ 0 ] );
  mydualmatrice.columnSet( 0 , 1 , mypixelbuffer[ 1 ] );
  mydualmatrice.columnSet( 0 , 2 , mypixelbuffer[ 2 ] );
  mydualmatrice.columnSet( 0 , 3 , mypixelbuffer[ 3 ] );
  mydualmatrice.columnSet( 0 , 4 , mypixelbuffer[ 4 ] );
  mydualmatrice.columnSet( 1 , 0 , mypixelbuffer[ 5 ] );
  mydualmatrice.columnSet( 1 , 1 , mypixelbuffer[ 6 ] );
  mydualmatrice.columnSet( 1 , 2 , mypixelbuffer[ 7 ] );
  mydualmatrice.columnSet( 1 , 3 , mypixelbuffer[ 8 ] );
  mydualmatrice.columnSet( 1 , 4 , mypixelbuffer[ 9 ] );
  mydualmatrice.updateDisplay();

  return;

}




/// @brief Arduino framework main loop. update the display with a new number on each matrix.
void loop() {

  // clear the old screen off
  mydualmatrice.clearAll();

  //mydualmatrice.


  // do stuff

  for ( uint8_t x = 0 ; x < 16 ; x++ ) {
      

    loadDigitIntoPixelBuffer( x );

    for ( int i = 0 ; i < 5 ; i++ ) {
      doscroll();
      sendtochip();
      delay( 100 );
    }

    mypixelbuffer[10] = 0b00000000;
    mypixelbuffer[11] = 0b00001000;
    mypixelbuffer[12] = 0b00010100;
    mypixelbuffer[13] = 0b00001000;
    mypixelbuffer[14] = 0b00000000;
    
    for ( int i = 0 ; i < 5 ; i++ ) {
      doscroll();
      sendtochip();
      delay( 100 );
    }


  }



}



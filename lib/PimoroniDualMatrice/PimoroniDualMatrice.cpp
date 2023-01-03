
// Pimoroni Dual Matrice Driver.

#include <PimoroniDualMatrice.h>



#include <Arduino.h>



/*
************************************* Private Methods.
*/






/// @brief Write a single byte to the chip.
/// @param address The address to write to.
/// @param data The byte to write to the give address.
void PimoroniDualMatrice::_chipByteSet( uint8_t address , uint8_t data ) {

    // send over a single byte.
    wire.beginTransmission( _i2cAddress );
    wire.write( address );
    wire.write( data );
    wire.endTransmission();

    // all done, return to caller.
    return;

}




































/*
********************************** Public Methods.
*/







PimoroniDualMatrice::PimoroniDualMatrice(/* args */)
{
}

PimoroniDualMatrice::~PimoroniDualMatrice()
{
}




/// @brief The initiator for the class.  Turns on i2c and resets the chip.
/// @param i2cAddress The i2c address of the chip.
void PimoroniDualMatrice::begin( uint8_t i2cAddress ) {

    // store my i2c address for later.
    _i2cAddress = i2cAddress;

    // bring up the wire library.
    wire.begin();

    // later is now, so send a reset to the chip.
    softwareReset();

    // update DM to turn on both matrices.
    matrixDisplayModeSet ( 0b11 );

    // turn the current down.
    matrixCurrentSet( 0b1010 );

    // at this point, everything is done, so return to caller.
    return;

}

















/// @brief Set a pixel to on or off.
/// @param matrix The matrix upon which the pixel resides. 0 for left, 1 for right.
/// @param xpos The x position of the pixel, starting at the top left.
/// @param ypos The y position of the pixel, starting at the top left.
/// @param state The state of the pixel.  1 for on, 0 for off.
void PimoroniDualMatrice::pixelSet( uint8_t matrix , uint8_t xpos , uint8_t ypos , uint8_t state ) {

    // set a pixel to on or off.
    if ( state ) {
        _pixelStateBuffer[ matrix ][ xpos ] |= ( 0b1 << ypos );
    }
    else {
        _pixelStateBuffer[ matrix ][ xpos ] &= ~( 0b1 << ypos );
    }
    // add done, return to caller.
    return;
}

/// @brief Get a pixels state as a uint8_t.
/// @param matrix The matrix in which the pixel resides.  0 for left, 1 for right.
/// @param xpos The x position of the pixel, starting at the top left.
/// @param ypos The y position of the pixel, starting at the top left.
/// @return The state of the pixel as a uint8_t.
uint8_t PimoroniDualMatrice::pixelGet( uint8_t matrix , uint8_t xpos , uint8_t ypos ) {
    // return the pixel state.
    return ( ( _pixelStateBuffer[ matrix ][ xpos ] >> ypos ) & 0b1 );
}


























// control register commands

// 0x00 Configuration Register.

// SSD Software Shutdown

/// @brief Turns the chip software off, and stops updating the display.
void PimoroniDualMatrice::softwareStateTurnOff() {
    _registercache_config |= 0b10000000;
    _chipByteSet( IS31FL3730_REG_CONFIG , _registercache_config );
    return;
}

/// @brief Turns the chip software on, and starts updating the display.
void PimoroniDualMatrice::softwareStateTurnOn() {
    _registercache_config &= 0b01111111;
    _chipByteSet( IS31FL3730_REG_CONFIG , _registercache_config );
   return;
}

/// @brief Gets the current software state from the chip.
/// @return The current software state as a uint8_t. 0 = normal operation, 1 = shutdown.
uint8_t PimoroniDualMatrice::softwareStateGet() {
    return ( ( _registercache_config & 0b10000000 ) >> 7 );
}


// DM Display Mode

/// @brief Sets the matris display mode.
/// @param state The matrix display mode. 0b00 1 only, 0b01 2 only, 0b11 1 and 2.
void PimoroniDualMatrice::matrixDisplayModeSet( uint8_t state ) {
    _registercache_config &= 0b11100111;
    _registercache_config |= ( ( state & 0b00000011 ) << 3 );
   _chipByteSet( IS31FL3730_REG_CONFIG , _registercache_config );
   return;
}

/// @brief Gets the matrix display mode.
/// @return The matrix display mode, as a uint8_t. 0b00 1 only, 0b01 2 only, 0b11 1 and 2.
uint8_t PimoroniDualMatrice::matrixDisplayModeGet() {
    return ( ( _registercache_config & 0b00011000 ) >> 3 );
}



// A_EN Audio Input Enable

// skipped due to not on this board.



// ADM Matrix Mode Selection

/// @brief Set the type of matrix connected.
/// @param state The type of matrix connected. 0b00 = 8x8, 0b01 = 7x9 , 0b10 = 6x10 , 0b11 5x11
void PimoroniDualMatrice::matrixModeSet( uint8_t state ) {
    _registercache_config &= 0b11111000;
    _registercache_config |= ( state & 0b00000111 );
    _chipByteSet( IS31FL3730_REG_CONFIG , _registercache_config );
    return;
}

/// @brief Gets the type of matrix connected.
/// @return The type of matrix connected as a uint8_t. 0b00 = 8x8, 0b01 = 7x9 , 0b10 = 6x10 , 0b11 5x11
uint8_t PimoroniDualMatrice::matrixModeGet() {
    return ( _registercache_config & 0b00000111 );
}





// 0x0c Update Column Register.

/// @brief Call to tell the chip to update the display.
void PimoroniDualMatrice::updateDisplay() {
    _chipByteSet( IS31FL3730_REG_UPDATE , 0x00 );
}



// 0x0D Lighting Effect Register.

// AGS Audio Input Gain Selection

// skipped audio stuff because not on this board.



// CS Current setting for display

/// @brief Set the electrical current output for the display.
/// @param state The electrical current to use for the display. See enum definitions under DUALMATRICECURRENT
void PimoroniDualMatrice::matrixCurrentSet( uint8_t state ) {
    _registercache_lighting &= 0b11110000;
    _registercache_lighting |= ( state & 0b00001111 );
    _chipByteSet( IS31FL3730_REG_LIGHTING , _registercache_lighting );
}

/// @brief Get the electrical current output for the display.
/// @return The electrical current to use for the display. See enum definitions under DUALMATRICECURRENT
uint8_t PimoroniDualMatrice::matrixCurrentGet() {
    return ( _registercache_lighting & 0b00000111 );
}





// 0x19 PWM Register.

/// @brief Set the pwm value for the display
/// @param state The pwm value to set. 0-128.
void PimoroniDualMatrice::displaypwmSet( uint8_t state ) {
    _registercache_pwm = state;
    _chipByteSet( IS31FL3730_REG_PWM , _registercache_pwm );
}

/// @brief Get the pwm value for the display.
/// @return The pwm value to set as a uint8_t. 0-128. 
uint8_t PimoroniDualMatrice::displaypwmGet() {
    return _registercache_pwm;
}



// 0xFF Reset Register.

/// @brief request the chip reset itself to default values.
void PimoroniDualMatrice::softwareReset() {
    _chipByteSet( IS31FL3730_REG_RESET , 0x00 );
}






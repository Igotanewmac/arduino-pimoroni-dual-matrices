
// Pimoroni Dual Matrice Driver.

#include <PimoroniDualMatrice.h>







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



/// @brief Gets a byte from the chip.
/// @param address The address to retereive.
/// @return The data at that address, as a uint8_t.
uint8_t PimoroniDualMatrice::_chipByteGet( uint8_t address ) {

    // send over the address
    wire.beginTransmission( _i2cAddress );
    wire.write( address );
    wire.endTransmission();

    // Request a byte back...
    wire.requestFrom( _i2cAddress , (uint8_t)(1) );
    while ( !wire.available() );
    return wire.read();

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

    // at this point, everything is done, so return to caller.
    return;

}






// control register commands

// 0x00 Configuration Register.

// SSD Software Shutdown

/// @brief Turns the chip software off, and stops updating the display.
void PimoroniDualMatrice::softwareStateTurnOff() {

}

/// @brief Turns the chip software on, and starts updating the display.
void PimoroniDualMatrice::softwareStateTurnOn() {

}

/// @brief Gets the current software state from the chip.
/// @return The current software state as a uint8_t. 0 = normal operation, 1 = shutdown.
uint8_t PimoroniDualMatrice::softwareStateGet() {
    return 0;
}


// DM Display Mode

/// @brief Sets the matris display mode.
/// @param state The matrix display mode. 0b00 1 only, 0b01 2 only, 0b11 1 and 2.
void PimoroniDualMatrice::matrixDisplayModeSet( uint8_t state ) {

}

/// @brief Gets the matrix display mode.
/// @return The matrix display mode, as a uint8_t. 0b00 1 only, 0b01 2 only, 0b11 1 and 2.
uint8_t PimoroniDualMatrice::matrixDisplayModeGet() {
    return 0;
}



// A_EN Audio Input Enable

// skipped due to not on this board.



// ADM Matrix Mode Selection

/// @brief Set the type of matrix connected.
/// @param state The type of matrix connected. 0b00 = 8x8, 0b01 = 7x9 , 0b10 = 6x10 , 0b11 5x11
void PimoroniDualMatrice::matrixModeSet( uint8_t state ) {

}

/// @brief Gets the type of matrix connected.
/// @return The type of matrix connected as a uint8_t. 0b00 = 8x8, 0b01 = 7x9 , 0b10 = 6x10 , 0b11 5x11
uint8_t PimoroniDualMatrice::matrixModeGet() {
    return 0;
}





// 0x0c Update Column Register.

/// @brief Call to tell the chip to update the display.
void PimoroniDualMatrice::updateDisplay() {

}



// 0x0D Lighting Effect Register.

// AGS Audio Input Gain Selection

// skipped audio stuff because not on this board.



// CS Current setting for display

/// @brief Set the electrical current output for the display.
/// @param state The electrical current to use for the display. See enum definitions under DUALMATRICECURRENT
void PimoroniDualMatrice::matrixCurrentSet( uint8_t state ) {

}

/// @brief Get the electrical current output for the display.
/// @return The electrical current to use for the display. See enum definitions under DUALMATRICECURRENT
uint8_t PimoroniDualMatrice::matrixCurrentGet() {
    return 0;
}





// 0x19 PWM Register.

/// @brief Set the pwm value for the display
/// @param state The pwm value to set. 0-128.
void PimoroniDualMatrice::displaypwmSet( uint8_t state ) {

}

/// @brief Get the pwm value for the display.
/// @return The pwm value to set as a uint8_t. 0-128. 
uint8_t PimoroniDualMatrice::displaypwmGet() {
    return 0;
}



// 0xFF Reset Register.

/// @brief request the chip reset itself to default values.
void PimoroniDualMatrice::softwareReset() {

}






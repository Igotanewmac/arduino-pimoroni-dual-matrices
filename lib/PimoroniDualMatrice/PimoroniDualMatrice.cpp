
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










/// @brief Write the pixel buffer to the chip.
/// @param matrix The matrix to update. 0 is left, 1 is right.
void PimoroniDualMatrice::_pixelBufferWriteToChip( uint8_t matrix ) {

    // split out into two routines because the board is wired funny
    if ( matrix == 0 ) {
        _pixelBufferWriteToChipBankLeft();
    }
    else {
        _pixelBufferWriteToChipBankRight();
    }

}




void PimoroniDualMatrice::_pixelBufferWriteToChipBankLeft() {

    // spam out the pixel buffer to bank 0x0E

    wire.beginTransmission( _i2cAddress );
    wire.write( IS31FL3730_REG_MATRIX_LEFT );
    wire.write( _pixelStateBuffer[ 0 ][ 0 ] );
    wire.write( _pixelStateBuffer[ 0 ][ 1 ] );
    wire.write( _pixelStateBuffer[ 0 ][ 2 ] );
    wire.write( _pixelStateBuffer[ 0 ][ 3 ] );
    wire.write( _pixelStateBuffer[ 0 ][ 4 ] );
    wire.endTransmission();

    return;

}








void PimoroniDualMatrice::_pixelBufferWriteToChipBankRight() {

    // spam out the pixel buffer to bank 0x01

    uint8_t tempbyte = 0x00;

    wire.beginTransmission( _i2cAddress );
    wire.write( IS31FL3730_REG_MATRIX_RIGHT );
    
    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & 0b1 ) << 0 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 1 ] & 0b1 ) << 1 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 2 ] & 0b1 ) << 2 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 3 ] & 0b1 ) << 3 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 4 ] & 0b1 ) << 4 );
    wire.write( tempbyte );

    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & ( 0b1 << 1 ) ) >> 1 );
    tempbyte |=   ( _pixelStateBuffer[ 1 ][ 1 ] & ( 0b1 << 1 ) );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 2 ] & ( 0b1 << 1 ) ) << 1 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 3 ] & ( 0b1 << 1 ) ) << 2  );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 4 ] & ( 0b1 << 1 ) ) << 3  );
    wire.write( tempbyte );
    
    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & ( 0b1 << 2 ) ) >> 2 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 1 ] & ( 0b1 << 2 ) ) >> 1 );
    tempbyte |=   ( _pixelStateBuffer[ 1 ][ 2 ] & ( 0b1 << 2 ) );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 3 ] & ( 0b1 << 2 ) ) << 1  );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 4 ] & ( 0b1 << 2 ) ) << 2  );
    wire.write( tempbyte );
    
    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & ( 0b1 << 3 ) ) >> 3 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 1 ] & ( 0b1 << 3 ) ) >> 2 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 2 ] & ( 0b1 << 3 ) ) >> 1 );
    tempbyte |=   ( _pixelStateBuffer[ 1 ][ 3 ] & ( 0b1 << 3 ) );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 4 ] & ( 0b1 << 3 ) ) << 1  );
    wire.write( tempbyte );
    
    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & ( 0b1 << 4 ) ) >> 4 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 1 ] & ( 0b1 << 4 ) ) >> 3 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 2 ] & ( 0b1 << 4 ) ) >> 2 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 3 ] & ( 0b1 << 4 ) ) >> 1  );
    tempbyte |=   ( _pixelStateBuffer[ 1 ][ 4 ] & ( 0b1 << 4 ) );
    wire.write( tempbyte );
    
    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & ( 0b1 << 5 ) ) >> 5 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 1 ] & ( 0b1 << 5 ) ) >> 4 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 2 ] & ( 0b1 << 5 ) ) >> 3 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 3 ] & ( 0b1 << 5 ) ) >> 2 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 4 ] & ( 0b1 << 5 ) ) >> 1 );
    wire.write( tempbyte );
    
    tempbyte = 0;
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 0 ] & ( 0b1 << 6 ) ) >> 6 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 1 ] & ( 0b1 << 6 ) ) >> 5 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 2 ] & ( 0b1 << 6 ) ) >> 4 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 3 ] & ( 0b1 << 6 ) ) >> 3 );
    tempbyte |= ( ( _pixelStateBuffer[ 1 ][ 4 ] & ( 0b1 << 6 ) ) >> 2 );
    wire.write( tempbyte );
    
    wire.endTransmission();

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










/// @brief Show a digit on the matrix
/// @param matrix The matrix to use. 0 for left, 1 for right.
/// @param digit The digit you wish to display.
void PimoroniDualMatrice::showDigit( uint8_t matrix , uint8_t digit ) {


    switch ( digit ) {
        
        // { 0x3E, 0x51, 0x49, 0x45, 0x3E },  // 30  48  0
        case 0x00:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x3E;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x51;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x45;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x3E;
            break;
        
        // { 0x00, 0x42, 0x7F, 0x40, 0x00 },  // 31  49  1
        case 0x01:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x00;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x42;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x7F;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x40;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x00;
            break;
        
        // { 0x42, 0x61, 0x51, 0x49, 0x46 },  // 32  50  2
        case 0x02:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x42;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x61;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x51;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x46;
            break;
        
        // { 0x21, 0x41, 0x45, 0x4B, 0x31 },  // 33  51  3
        case 0x03:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x21;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x41;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x45;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x4B;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x31;
            break;
        
        // { 0x18, 0x14, 0x12, 0x7F, 0x10 },  // 34  52  4
        case 0x04:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x18;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x14;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x12;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x7F;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x10;
            break;
        
        // { 0x27, 0x45, 0x45, 0x45, 0x39 },  // 35  53  5
        case 0x05:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x27;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x45;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x45;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x45;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x39;
            break;
        
        // { 0x3C, 0x4A, 0x49, 0x49, 0x30 },  // 36  54  6
        case 0x06:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x3C;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x4A;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x30;
            break;
        
        // { 0x01, 0x01, 0x71, 0x0D, 0x03 },  // 37  55  7
        case 0x07:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x01;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x01;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x71;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x0D;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x03;
            break;
        
        // { 0x36, 0x49, 0x49, 0x49, 0x36 },  // 38  56  8
        case 0x08:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x36;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x36;
            break;
        
        // { 0x06, 0x49, 0x49, 0x29, 0x1E },  // 39  57  9
        case 0x09:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x06;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x29;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x1E;
            break;
        
        // { 0x7C, 0x12, 0x11, 0x12, 0x7C },  // 41  65  A
        case 0x0A:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x7C;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x12;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x11;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x12;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x7C;
            break;
        
        // { 0x7F, 0x49, 0x49, 0x49, 0x36 },  // 42  66  B
        case 0x0B:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x7F;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x36;
            break;
        
        // { 0x3E, 0x41, 0x41, 0x41, 0x22 },  // 43  67  C
        case 0x0C:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x3E;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x41;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x41;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x41;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x22;
            break;
        
        // { 0x7F, 0x41, 0x41, 0x22, 0x1C },  // 44  68  D
        case 0x0D:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x7F;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x41;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x41;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x22;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x1C;
            break;
        
        // { 0x7F, 0x49, 0x49, 0x49, 0x41 },  // 45  69  E
        case 0x0E:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x7F;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x49;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x41;
            break;
        
        // { 0x7F, 0x09, 0x09, 0x09, 0x01 },  // 46  70  F
        case 0x0F:
            _pixelStateBuffer[ matrix ][ 0 ] = 0x7F;
            _pixelStateBuffer[ matrix ][ 1 ] = 0x09;
            _pixelStateBuffer[ matrix ][ 2 ] = 0x09;
            _pixelStateBuffer[ matrix ][ 3 ] = 0x09;
            _pixelStateBuffer[ matrix ][ 4 ] = 0x01;
            break;
        
        default:
            break;
        
    }

    return;
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
    _pixelBufferWriteToChip( 0 );
    _pixelBufferWriteToChip( 1 );
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






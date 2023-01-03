
// Pimoroni Dual Matrice Driver.

#ifndef PIMORONIDUALMATRICEINCLUDEGUARD
#define PIMORONIDUALMATRICEINCLUDEGUARD


// pull in the wire library.
#ifndef wire
#include <Wire.h>
#define wire Wire
#endif





#define IS31FL3730_REG_CONFIG 0x00
#define IS31FL3730_REG_MATRIX_ONE 0x01
#define IS31FL3730_REG_MATRIX_TWO 0x0E
#define IS31FL3730_REG_UPDATE 0x0C
#define IS31FL3730_REG_LIGHTING 0x0D
#define IS31FL3730_REG_PWM 0x19
#define IS31FL3730_REG_RESET 0xFF




#define N01 0b00000
#define N02 0b01110
#define N03 0b01010
#define N04 0b01010
#define N05 0b01010
#define N06 0b01110
#define N07 0b00000


#define N11 0b00000
#define N12 0b01100
#define N13 0b00100
#define N14 0b00100
#define N15 0b00100
#define N16 0b01110
#define N17 0b00000


#define N21 0b00000
#define N22 0b01110
#define N23 0b00010
#define N24 0b00100
#define N25 0b01000
#define N26 0b01110
#define N27 0b00000


#define N31 0b00000
#define N32 0b01110
#define N33 0b00010
#define N34 0b00110
#define N35 0b00010
#define N36 0b01110
#define N37 0b00000



#define N41 0b00000
#define N42 0b00010
#define N43 0b00110
#define N44 0b01010
#define N45 0b01110
#define N46 0b00010
#define N47 0b00000


#define N51 0b00000
#define N52 0b01110
#define N53 0b01000
#define N54 0b01100
#define N55 0b00010
#define N56 0b01100
#define N57 0b00000



#define N61 0b00000
#define N62 0b01110
#define N63 0b01000
#define N64 0b01100
#define N65 0b01010
#define N66 0b01110
#define N67 0b00000


#define N71 0b00000
#define N72 0b01110
#define N73 0b00010
#define N74 0b00100
#define N75 0b01000
#define N76 00.1000
#define N77 0b00000


#define N81 0b00000
#define N82 0b01110
#define N83 0b01010
#define N84 0b01110
#define N85 0b01010
#define N86 0b01110
#define N87 0b00000


#define N91 0b00000
#define N92 0b01110
#define N93 0b01010
#define N94 0b01110
#define N95 0b00010
#define N96 0b00100
#define N97 0b00000























class PimoroniDualMatrice
{

private:
    
    /// @brief The i2c address of the chip.
    uint8_t _i2cAddress;

    /// @brief Write a single byte to the chip.
    /// @param address The address to write to.
    /// @param data The byte to write to the give address.
    void _chipByteSet( uint8_t address , uint8_t data );

    /// @brief cache for control register
    uint8_t _registercache_config = 0b00011000;

    /// @brief cache for lighting effect register
    uint8_t _registercache_lighting = 0b00000000;

    /// @brief cache for pwm register
    uint8_t _registercache_pwm = 0b10000000;


    /// @brief Two 5x8 arrays of bitmap cache
    uint8_t _pixelStateBuffer[2][5] = { { 0 } };

    /// @brief Thebuffer for the decimal points.
    uint8_t _pixelDecimalPointBuffer = 0;




    // pixel buffer writes!

    /// @brief Write the pixel buffer to the chip.
    /// @param matrix The matrix to update. 0 is left, 1 is right.
    void _pixelBufferWriteToChip( uint8_t matrix );

    /// @brief Utility function for left bank translation.
    void _pixelBufferWriteToChipBankLeft();

    /// @brief utility function for right bank translation.
    void _pixelBufferWriteToChipBankRight();




public:
    
    /// @brief Class Constructor.
    PimoroniDualMatrice();

    /// @brief Class Destructor.
    ~PimoroniDualMatrice();


    /// @brief The initiator for the class.  Turns on i2c and resets the chip.
    /// @param i2cAddress The i2c address of the chip.
    void begin( uint8_t i2cAddress );


    



    // pixel control!


    /// @brief Set a pixel to on or off.
    /// @param matrix The matrix upon which the pixel resides. 0 for left, 1 for right.
    /// @param xpos The x position of the pixel, starting at the top left.
    /// @param ypos The y position of the pixel, starting at the top left.
    /// @param state The state of the pixel.  1 for on, 0 for off.
    void pixelSet( uint8_t matrix , uint8_t xpos , uint8_t ypos , uint8_t state );

    /// @brief Get a picels state as a uint8_t.
    /// @param matrix The matrix in which the pixel resides.  0 for left, 1 for right.
    /// @param xpos The x position of the pixel, starting at the top left.
    /// @param ypos The y position of the pixel, starting at the top left.
    /// @return The state of the pixel as a uint8_t.
    uint8_t pixelGet( uint8_t matrix , uint8_t xpos , uint8_t ypos );








    /// @brief Show a digit on the matrix
    /// @param matrix The matrix to use. 0 for left, 1 for right.
    /// @param digit The digit you wish to display.
    void showDigit( uint8_t matrix , uint8_t digit );
















    // control register commands

    // 0x00 Configuration Register.

    // SSD Software Shutdown

    /// @brief Turns the chip software off, and stops updating the display.
    void softwareStateTurnOff();

    /// @brief Turns the chip software on, and starts updating the display.
    void softwareStateTurnOn();

    /// @brief Gets the current software state from the chip.
    /// @return The current software state as a uint8_t. 0 = normal operation, 1 = shutdown.
    uint8_t softwareStateGet();


    // DM Display Mode

    /// @brief Sets the matris display mode.
    /// @param state The matrix display mode. 0b00 1 only, 0b01 2 only, 0b11 1 and 2.
    void matrixDisplayModeSet( uint8_t state );

    /// @brief Gets the matrix display mode.
    /// @return The matrix display mode, as a uint8_t. 0b00 1 only, 0b01 2 only, 0b11 1 and 2.
    uint8_t matrixDisplayModeGet();



    // A_EN Audio Input Enable

    // skipped due to not on this board.



    // ADM Matrix Mode Selection

    /// @brief Set the type of matrix connected.
    /// @param state The type of matrix connected. 0b00 = 8x8, 0b01 = 7x9 , 0b10 = 6x10 , 0b11 5x11
    void matrixModeSet( uint8_t state );

    /// @brief Gets the type of matrix connected.
    /// @return The type of matrix connected as a uint8_t. 0b00 = 8x8, 0b01 = 7x9 , 0b10 = 6x10 , 0b11 5x11
    uint8_t matrixModeGet();





    // 0x0c Update Column Register.

    /// @brief Call to tell the chip to update the display.
    void updateDisplay();



    // 0x0D Lighting Effect Register.

    // AGS Audio Input Gain Selection

    // skipped audio stuff because not on this board.



    // CS Current setting for display

    /// @brief Set the electrical current output for the display.
    /// @param state The electrical current to use for the display. See enum definitions under DUALMATRICECURRENT
    void matrixCurrentSet( uint8_t state );

    /// @brief Get the electrical current output for the display.
    /// @return The electrical current to use for the display. See enum definitions under DUALMATRICECURRENT
    uint8_t matrixCurrentGet();





    // 0x19 PWM Register.

    /// @brief Set the pwm value for the display
    /// @param state The pwm value to set. 0-128.
    void displaypwmSet( uint8_t state );

    /// @brief Get the pwm value for the display.
    /// @return The pwm value to set as a uint8_t. 0-128. 
    uint8_t displaypwmGet();



    // 0xFF Reset Register.

    /// @brief request the chip reset itself to default values.
    void softwareReset();



    




};













#endif








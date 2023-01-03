
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

    void _pixelBufferWriteToChip( uint8_t matrix );






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








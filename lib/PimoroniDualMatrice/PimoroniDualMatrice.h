
// Pimoroni Dual Matrice Driver.

#ifndef PIMORONIDUALMATRICEINCLUDEGUARD
#define PIMORONIDUALMATRICEINCLUDEGUARD


// pull in the wire library.
#ifndef wire
#include <Wire.h>
#define wire Wire
#endif



class PimoroniDualMatrice
{

private:
    
    /// @brief The i2c address of the chip.
    uint8_t _i2cAddress;





public:
    
    /// @brief Class Constructor.
    PimoroniDualMatrice();

    /// @brief Class Destructor.
    ~PimoroniDualMatrice();


    /// @brief The initiator for the class.  Turns on i2c and resets the chip.
    /// @param i2cAddress The i2c address of the chip.
    void begin( uint8_t i2cAddress );






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








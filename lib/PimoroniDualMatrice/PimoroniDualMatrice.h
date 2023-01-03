
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


    void softwareStateTurnOff();

    void softwareStateTurnOn();

    void softwareStateGet();


    // DM Display Mode

    void displayModeSet( uint8_t state );

    uint8_t displayModeGet();



    // A_EN Audio Input Enable

    void audioInputSet( uint8_t state );

    uint8_t audioInputGet();



    // ADM Matrix Mode Selection

    void matrixModeSet( uint8_t );

    uint8_t matrixModeGet();





    // 0x0c Update Column Register.

    void updateDisplay();



    // 0x0D Lighting Effect Register.

    // AGS Audio Input Gain Selection

    void audioGainSet( uint8_t state );

    uint8_t audioGainGet();


    // CS Current setting for display

    void matrixCurrentSet( uint8_t state );

    uint8_t matrixCurrentGet();




    // 0x19 PWM Register.

    void displaypwmSet( uint8_t state );

    uint8_t displaypwmGet();



    // 0xFF Reset Register.

    void softwareReset();
    


    




};













#endif








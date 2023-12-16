//
// Project_1_Prosthetic Arm
// Evan Varga & Oriekaose Agholor
//
// In this Lab, we will utilize the UART and SPI.
// The UART is available over USB debug virtual serial port on the evaluation board)
// will be configured for 115,200 baud, 8-n-1 mode.
// All characters received on the UART are transmitted back to the UART and the SPI.
//
//

//! - SSI0 peripheral
//! - GPIO Port A peripheral (for SSI0 pins)
//! - SSI0Clk - PA2
//! - SSI0Fss - PA3
//! - SSI0Rx  - PA4
//! - SSI0Tx  - PA5
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of SSI0.
//! - UART0 peripheral
//! - GPIO Port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1

//! Connections, for example, we can connect the TIVA C with an Arduino Micro, or any micro supporting SSI
//! Arduino
//! 10 CS
//! 12 MISO
//! 11 MOSI
//! 13 CLK

//! TIVA:
//! SSI0Clk - PA2
//! SSI0Fss - PA3
//! SSI0Rx  - PA4
//! SSI0Tx  - PA5

// Assignment:
// Add a GPT (0, 1), when the UART command is sent,
// flash the corresponding LED continuously,
// if any command other than 1,!, 2@, 3,# flash all the LEDs for 5s, then turn them all OFF


// {possibility of using this lab as a project}:
// Integrate Lab_4 (Timers), ADC, and PWM with this Lab:
// Creata n application with the following features:
// Control the brightness of the LEDs (PWM)
// Control the servo motor (PWM)
// Flash the LED at certain rate (1HZ-Timer)
// faults, pushbuttons, etc...



// System functions prototype include section:
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pwm.h"
#include "driverlib/adc.h"

// UART & SSI Prototype functions
#include "driverlib/uart.h"
#include "driverlib/ssi.h"


// Interrupts prototype functions
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

// Timer prototype functions
#include "driverlib/timer.h"


// Hardware Abstraction
// LEDs Pin HW Positions
#define RED_LED_IO            GPIO_PIN_1  // PF0
#define BLUE_LED_IO           GPIO_PIN_2  // PF4

#define GREEN_LED_IO          GPIO_PIN_3  // PF3
#define MOTOR_IO              GPIO_PIN_1  // PD1


// prototype of the uart send function, this function is used to echo back the sent character
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);
#define SendDataOnUART(a)  UARTSend((uint8_t *)a, strlen(a));


// LEDs Pin Positions
#define RED_LED               0x02  // PF0
#define GREEN_LED             0x08  // PF3
#define BLUE_LED              0x04  // PF4
#define YELLOW_LED            (RED_LED   | GREEN_LED)
#define SKY_BLUE_LED          (GREEN_LED | BLUE_LED)
#define PINK_LED              (RED_LED   | BLUE_LED)
#define WHITE_LED             (RED_LED   | GREEN_LED | BLUE_LED)



// FINGER Pin Positions
#define FINGER_0            GPIO_PIN_4  // PE4
#define FINGER_1            GPIO_PIN_1  // PF1
#define FINGER_2            GPIO_PIN_2  // PF2
#define FINGER_3            GPIO_PIN_3  // PF3
#define FINGER_4            GPIO_PIN_5  // PE5

// COMMUNICATION Pin Positions
#define COMM_0              GPIO_PIN_4  // PC4
#define COMM_1              GPIO_PIN_5  // PC5
#define COMM_2              GPIO_PIN_6  // PC6
#define COMM_3              GPIO_PIN_7  // PC7


#define LED_GPIO_MASK      (RED_LED|BLUE_LED|GREEN_LED)


#define FALSE 0
#define TRUE  1
#define LED_OFF           FALSE

// Program variables with Init values:
uint8_t LED_Command_R  = 0;
uint8_t LED_Command_G  = 0;
uint8_t LED_Command_B  = 0;

uint8_t ButtonState_L  = 0;
uint8_t ButtonState_R  = 0;
uint8_t ButtonState_RL = 0;


uint8_t Button_Pressed_R = FALSE;
uint8_t Button_Pressed_L = FALSE;


uint8_t ButtonStates   = 0;

// Communication Signals
int32_t  UART_Received_Char;
uint32_t UART_Previous = 0;
uint32_t SSI_ARD_Received_Char;

#define ASCII_DIGIT_1    49
#define ASCII_DIGIT_2    50

// For Timers
// Timer occurrences, used to count number of times the timer has fired
uint32_t Timer0_Occurances = 0;
uint32_t T0MAX = 0;
#define TIMER_0_MAX_OCCURANCES     T0MAX  /* 5 ON/OFF occurrences @ 1000ms */
uint32_t TIMER_0_Period;


// Program variables with Init values:
uint8_t LED_Command = LED_OFF;


void FingerCounting(uint32_t, uint32_t*, uint32_t*, uint32_t*, uint32_t*, uint32_t*);

void CommunicationPinSet(uint32_t);

uint32_t F0MotorDuty = 1;
uint32_t F1MotorDuty = 1;
uint32_t F2MotorDuty = 1;
uint32_t F3MotorDuty = 1;
uint32_t F4MotorDuty = 1;
uint32_t count = 0;

uint32_t c0 = 0;
uint32_t c1 = 0;
uint32_t c2 = 0;
uint32_t c3 = 0;

uint32_t SequenceData = 0;
uint32_t rps_choice = 0;

uint32_t pianoPosition = 0;

uint32_t MaryHadALittleLamb[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 3, 3, 3, 0, 4, 4, 4, 0, 3, 3, 3, 0, 2, 2,
                                 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 0, 0, 0, 0, 2, 2,
                                 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 3, 3, 3, 0, 4, 4, 4, 0, 3, 3, 3, 0, 2, 2,
                                 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 3, 3, 3, 0, 3, 3, 3, 0, 2, 2, 2, 0, 3, 3, 3, 0, 4, 4};

int main(void)
    {




    //uint8_t PreviousR = BUTTON_OFF;
    //uint8_t PreviousL = BUTTON_OFF;
    //uint8_t PreviousRL = BUTTON_OFF;

    uint8_t RightStatus = false;
    uint8_t LeftStatus = false;

    //first part of main is setup


    //Set the clock frequency to 40MHz
    SysCtlClockSet(SYSCTL_OSC_MAIN|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_5);

    // This function enables a peripheral, which peripheral? and why?
    // At power-up, all peripherals are disabled;
    // Peripherals must be enabled in order to operate or respond to register
    // reads/writes.
    //
    // 1- Enable the GPIO port that is used for the on-board LED and for the Switch
    // LEDs & the Switch are both connected to PORTF:

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

    //ADC_Configuration Function
    //Enable Peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    //Initialize PortE
    GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);
    //Configure Sequencer (Arbitrary picked 3 Sequence, 0 for priority)
    ADCSequenceConfigure(ADC0_BASE,3,ADC_TRIGGER_PROCESSOR,0);
    //Configure Sequence Step
    ADCSequenceStepConfigure(ADC0_BASE,3,0,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
    //Enable Sequencer
    ADCSequenceEnable(ADC0_BASE,3);
    //Clear Flag for Conversion Complete
    ADCIntClear(ADC0_BASE,3);
    //


    // Configure GPIO Communication pins
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, COMM_0 | COMM_1 | COMM_2 | COMM_3);

    // 2- SET THE LEDS AS OUTPUTS with PWM:
    // Enable the GPIO pin for the LED (PF1, PF2 and PF3)

    GPIOPinTypePWM(GPIO_PORTF_BASE, FINGER_1 | FINGER_2 | FINGER_3);
    GPIOPinTypePWM(GPIO_PORTE_BASE, FINGER_0 | FINGER_4);

    GPIOPinTypePWM(GPIO_PORTD_BASE, MOTOR_IO);


    // configure GPIO pin to PWM generator
    GPIOPinConfigure(GPIO_PE4_M1PWM2);      // Finger 0
    GPIOPinConfigure(GPIO_PF1_M1PWM5);      // Finger 1
    GPIOPinConfigure(GPIO_PF2_M1PWM6);      // Finger 2
    GPIOPinConfigure(GPIO_PF3_M1PWM7);      // Finger 3
    GPIOPinConfigure(GPIO_PE5_M1PWM3);      // Finger 4


    //configure PWM generator Mode
   // PWMGenConfigure(PWM1_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_1,PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_2,PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_DOWN);

    //configure the PWM system clock to 2.5MHz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);

    //set PWM period
    //PWMGenPeriodSet(PWM1_BASE,PWM_GEN_0,41667);
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_1,41667);
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_2,41667);
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_3,41667);

    //set pulse width
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_2,F0MotorDuty);
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_5,F1MotorDuty);
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_6,F2MotorDuty);
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_7,F3MotorDuty);
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_3,F4MotorDuty);

    //enable pins to turn on
    PWMOutputState(PWM1_BASE,PWM_OUT_2_BIT,true);
    PWMOutputState(PWM1_BASE,PWM_OUT_5_BIT,true);
    PWMOutputState(PWM1_BASE,PWM_OUT_6_BIT,true);
    PWMOutputState(PWM1_BASE,PWM_OUT_7_BIT,true);
    PWMOutputState(PWM1_BASE,PWM_OUT_3_BIT,true);

    //enable generator
    //PWMGenEnable(PWM1_BASE,PWM_GEN_0);
    PWMGenEnable(PWM1_BASE,PWM_GEN_1);
    PWMGenEnable(PWM1_BASE,PWM_GEN_2);
    PWMGenEnable(PWM1_BASE,PWM_GEN_3);

    //
    // 3-Set each of the button GPIO pins as an input with a pull-up.
    //
    //GPIODirModeSet(GPIO_PORTF_BASE,   (LEFT_BUTTON | RIGHT_BUTTON), GPIO_DIR_MODE_IN);
    //GPIOPadConfigSet(GPIO_PORTF_BASE, (LEFT_BUTTON | RIGHT_BUTTON), GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);







    //
    // Set the clocking to run directly from the crystal.
    //
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //
    // LEDs & Pushbuttons:
    //
    // Used for buttons and LEDs
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // SET THE LEDS AS OUTPUTS:
    // Enable the GPIO pin for the LED (PF1, PF2 and PF3)
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED);

    //GPIOPinWrite(GPIO_PORTF_BASE, (RED_LED), (RED_LED));
    //GPIOPinWrite(GPIO_PORTF_BASE, (BLUE_LED), (LED_OFF));

    //
    // Set each of the button GPIO pins as an input with a pull-up.
    //
    //GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    //GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // UART starts here:
    //
    // Enable the peripheralS:.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_TWO |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);


    // SSI starts here:
    //
    // Enable the SSI peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    //
    // SSI0 is used with PortA[5:2].
    // GPIO port A needs to be enabled so these pins can be used.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the GPIO settings for the SSI pins.  This function also gives
    // control of these pins to the SSI hardware.  Consult the data sheet to
    // see which functions are allocated per pin.
    // The pins are assigned as follows:
    //      PA5 - SSI0Tx
    //      PA4 - SSI0Rx
    //      PA3 - SSI0Fss
    //      PA2 - SSI0CLK
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);

    //
    // Configure and enable the SSI port for SPI master mode.
    // Use SSI0 system clock supply, idle clock level low and active low clock in
    // freescale SPI mode,
    // Master mode, 1MHz SSI frequency, and 8-bit data.
    // Set the polarity of the SSI clock when the SSI
    // unit is idle.
    // Configure what clock edge you want to capture data on.
    //
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 8);

    //
    // Enable the SSI0 module.
    //
    SSIEnable(SSI0_BASE);


    //
    // Prompt for text to be entered.
    //
    SendDataOnUART("\033cReady...:\n ")
    //Turn ON the GREN LED
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);

    // Timer Setup
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Configure the two 32-bit as periodic timers
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TIMER_0_Period = 40000000;      // 1000 ms
    TimerLoadSet(TIMER0_BASE, TIMER_A, TIMER_0_Period);   // 1 s
    IntEnable(INT_TIMER0A);
    // Enable the Timer Timeout, means a callback function will be executed
    // Timer ISR function should be added to the interrupt vector
    // This is done by enabling the TIME_OUT Feature in the timer
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();






    //
    // Loop forever echoing data through the UART.
    //
    while(1)
    {
        //Polling
        //Ask ADC to read pins
        ADCProcessorTrigger(ADC0_BASE,3);
        //Read the ADC read done Status
        while(!ADCIntStatus(ADC0_BASE,3,false))
        {
        }
        //Read the ADC Value
        ADCSequenceDataGet(ADC0_BASE,3,&SequenceData);
        //Clear Flag saying Value Ready
        ADCIntClear(ADC0_BASE,3);
        //
        //

        //if (UART_Previous != UART_Received_Char)
        //{
          // Based on which button is pressed, set individual LEDs command:
        switch (UART_Received_Char)
        {
          case '1':   //Number 1
                F0MotorDuty = 1250;
                F1MotorDuty = 1250;
                F2MotorDuty = 6250;
                F3MotorDuty = 6250;
                F4MotorDuty = 6250;

                //F0MotorDuty = 1250;
                //F1MotorDuty = 6250;
                //F2MotorDuty = 6250;
                //F3MotorDuty = 1250;
                //F4MotorDuty = 6250;

                TimerDisable(TIMER0_BASE, TIMER_A);
                Timer0_Occurances = 0;
                count = 0;
                CommunicationPinSet(1);
           break;

           case '2':   //Number 2
                 F0MotorDuty = 1250;
                 F1MotorDuty = 1250;
                 F2MotorDuty = 1250;
                 F3MotorDuty = 6250;
                 F4MotorDuty = 6250;
                 TimerDisable(TIMER0_BASE, TIMER_A);
                 Timer0_Occurances = 0;
                 count = 0;
                 CommunicationPinSet(1);
            break;

            case '3':   //Number 3
                 F0MotorDuty = 1250;
                 F1MotorDuty = 1250;
                 F2MotorDuty = 1250;
                 F3MotorDuty = 1250;
                 F4MotorDuty = 6250;
                 TimerDisable(TIMER0_BASE, TIMER_A);
                 Timer0_Occurances = 0;
                 count = 0;
                 CommunicationPinSet(1);
             break;

             case '4':   //Number 4
                  F0MotorDuty = 1250;
                  F1MotorDuty = 1250;
                  F2MotorDuty = 1250;
                  F3MotorDuty = 1250;
                  F4MotorDuty = 1250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(1);
             break;

             case '5':  //Open Hand/Paper/Number 5
                  F0MotorDuty = 6250;
                  F1MotorDuty = 1250;
                  F2MotorDuty = 1250;
                  F3MotorDuty = 1250;
                  F4MotorDuty = 1250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(1);
              break;

              case '!':  //Okay
                  F0MotorDuty = 2000;
                  F1MotorDuty = 4750;
                  F2MotorDuty = 3750;
                  F3MotorDuty = 3250;
                  F4MotorDuty = 2750;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(2);
              break;

              case '@':   //Rock and Roll
                  F0MotorDuty = 1250;
                  F1MotorDuty = 1250;
                  F2MotorDuty = 6250;
                  F3MotorDuty = 6250;
                  F4MotorDuty = 1250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(3);
              break;

              case '#':   //Hang Loose
                  F0MotorDuty = 6250;
                  F1MotorDuty = 6250;
                  F2MotorDuty = 6250;
                  F3MotorDuty = 6250;
                  F4MotorDuty = 1250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(4);
              break;

              case '8':   //Thumbs Up
                  F0MotorDuty = 6250;
                  F1MotorDuty = 6250;
                  F2MotorDuty = 6250;
                  F3MotorDuty = 6250;
                  F4MotorDuty = 6250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(5);
              break;

              case '*':   //Thumbs Down
                  F0MotorDuty = 6250;
                  F1MotorDuty = 6250;
                  F2MotorDuty = 6250;
                  F3MotorDuty = 6250;
                  F4MotorDuty = 6250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(6);
              break;

              case '%':   //Fist Bump
                  F0MotorDuty = 1250;
                  F1MotorDuty = 6250;
                  F2MotorDuty = 6250;
                  F3MotorDuty = 6250;
                  F4MotorDuty = 6250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(8);
              break;

              case '^':   //Spider-Man
                  F0MotorDuty = 6250;
                  F1MotorDuty = 1250;
                  F2MotorDuty = 6250;
                  F3MotorDuty = 6250;
                  F4MotorDuty = 1250;
                  TimerDisable(TIMER0_BASE, TIMER_A);
                  Timer0_Occurances = 0;
                  count = 0;
                  CommunicationPinSet(7);
              break;

              case '6':   //Count 1-5
                  if(UART_Previous != UART_Received_Char)
                  {
                      TimerLoadSet(TIMER0_BASE, TIMER_A, TIMER_0_Period);   // 1 s
                      TimerEnable(TIMER0_BASE, TIMER_A);
                      T0MAX = 5;
                      Timer0_Occurances = 0;
                      count = 0;
                  }
                  CommunicationPinSet(9);
              break;

              case '7':     //Rock Paper Scissors game
                  if(UART_Previous != UART_Received_Char)
                  {
                      F0MotorDuty = 1250;
                      F1MotorDuty = 6250;
                      F2MotorDuty = 6250;
                      F3MotorDuty = 6250;
                      F4MotorDuty = 6250;
                      TimerLoadSet(TIMER0_BASE, TIMER_A, TIMER_0_Period);   // 1 s
                      TimerEnable(TIMER0_BASE, TIMER_A);
                      T0MAX = 20;
                      Timer0_Occurances = 0;
                      count = 0;
                      CommunicationPinSet(10);
                  }
                  //count = 0;
              break;

              case 'w':  //Open Hand/Paper/Number 5
                   F0MotorDuty = 6250;
                   F1MotorDuty = 1250;
                   F2MotorDuty = 1250;
                   F3MotorDuty = 1250;
                   F4MotorDuty = 1250;
                   TimerDisable(TIMER0_BASE, TIMER_A);
                   Timer0_Occurances = 0;
                   count = 0;
                   CommunicationPinSet(11);
             break;

              case 'j':   //Count 1-5
                  if(UART_Previous != UART_Received_Char)
                  {
                      TimerLoadSet(TIMER0_BASE, TIMER_A, TIMER_0_Period/8);   // 250 ms
                      TimerEnable(TIMER0_BASE, TIMER_A);
                      T0MAX = 192;
                      Timer0_Occurances = 0;
                      count = 0;
                      CommunicationPinSet(12);
                  }
              break;

              default:
                  F0MotorDuty = 1;
                  F1MotorDuty = 1;
                  F2MotorDuty = 1;
                  F3MotorDuty = 1;
                  F4MotorDuty = 1;

          }

          //Note that thumb is inverted
          //MotorDuty=1250 - Finger is fully opened
          //MotorDuty=6250 - Finger is fully closed

          PWMPulseWidthSet(PWM1_BASE,PWM_OUT_2,F0MotorDuty);        //Thumb
          PWMPulseWidthSet(PWM1_BASE,PWM_OUT_5,F1MotorDuty);        //Pointer
          PWMPulseWidthSet(PWM1_BASE,PWM_OUT_6,F2MotorDuty);        //Middle
          PWMPulseWidthSet(PWM1_BASE,PWM_OUT_7,F3MotorDuty);        //Ring
          PWMPulseWidthSet(PWM1_BASE,PWM_OUT_3,F4MotorDuty);        //Pinky

        //}

        UART_Previous = UART_Received_Char;

         // Write to LED HW Port
         GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED|BLUE_LED, (LED_Command_R|LED_Command_G|LED_Command_B));


    }
}



//*****************************************************************************
//*5
// The UART interrupt handler.
//
//*****************************************************************************
void ISR_UARTIntHandler(void)
{
    uint32_t ui32Status;
    //
    // Blink the LED to show a character transfer is occurring.
    //

    //Turn ON the BLUE LED & Turn OFF the GREEN LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, LED_OFF);

    //
    // Get the interrupt status.
    //
    ui32Status = UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        UART_Received_Char = UARTCharGetNonBlocking(UART0_BASE);
        UARTCharPutNonBlocking(UART0_BASE, UART_Received_Char);


        // Send the received UART Char on the SSI port to the Arduino
        SSIDataPutNonBlocking(SSI0_BASE, UART_Received_Char);

        // After sending the received UART byte, capture the received SSI byte from the Arduino
        SSIDataGetNonBlocking(SSI0_BASE, &SSI_ARD_Received_Char);



        //
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        //
        SysCtlDelay(SysCtlClockGet() / (1000 * 3));
    }

    //Turn OFF the BLUE LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, LED_OFF);
}


//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
//*****************************************************************************
void ISR_Timer0IntHandler(void)
{
    // ACK timer 0 by clearing the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Check number of occurrences, if more than a certain value, disable the timer interrupt
    if (UART_Received_Char == '6')
     {
        count++;
        FingerCounting(count, &F0MotorDuty, &F1MotorDuty, &F2MotorDuty, &F3MotorDuty, &F4MotorDuty);
     }
    else if (UART_Received_Char == '7')
    {
        count++;
        if (count == 5)
        {
            rps_choice = SequenceData % 3;
            TimerDisable(TIMER0_BASE, TIMER_A);
            Timer0_Occurances = 0;
            count = 0;
            //UART_Received_Char = 'p';
            CommunicationPinSet(14);


            if (rps_choice == 0)
            {
                F0MotorDuty = 1250;
                F1MotorDuty = 6250;
                F2MotorDuty = 6250;
                F3MotorDuty = 6250;
                F4MotorDuty = 6250;
            }
            else if (rps_choice == 1)
            {
                F0MotorDuty = 6250;
                F1MotorDuty = 1250;
                F2MotorDuty = 1250;
                F3MotorDuty = 1250;
                F4MotorDuty = 1250;
            }
            else
            {
                F0MotorDuty = 1250;
                F1MotorDuty = 1250;
                F2MotorDuty = 1250;
                F3MotorDuty = 6250;
                F4MotorDuty = 6250;
            }
        }
    }
    else if (UART_Received_Char == 'j')
    {
        count++;
        pianoPosition = MaryHadALittleLamb[count];

        if (count == 48)
            CommunicationPinSet(15);

        switch (pianoPosition)
        {
        case 0:
            F1MotorDuty = 2750;
            F2MotorDuty = 2750;
            F3MotorDuty = 2750;
            F4MotorDuty = 3750;
        break;

        case 1:
            F4MotorDuty = 3750;
            F1MotorDuty = 2750;
            F2MotorDuty = 2750;
            F3MotorDuty = 2750;
        break;

        case 2:
            F2MotorDuty = 2750;
            F1MotorDuty = 4000;
            F3MotorDuty = 2750;
            F4MotorDuty = 3750;
        break;

        case 3:
            F1MotorDuty = 2750;
            F3MotorDuty = 2750;
            F2MotorDuty = 4000;
            F4MotorDuty = 3750;
        break;

        case 4:
            F1MotorDuty = 2750;
            F2MotorDuty = 2750;
            F4MotorDuty = 3750;
            F3MotorDuty = 4000;
        break;


        default:
            F1MotorDuty = 1250;
            F2MotorDuty = 1250;
            F3MotorDuty = 1250;
            F4MotorDuty = 1250;
            TimerDisable(TIMER0_BASE, TIMER_A);
        }
    }
    else
     {
       TimerDisable(TIMER0_BASE, TIMER_A);
       Timer0_Occurances = 0;
       count = 0;
     }

    if(++Timer0_Occurances >= TIMER_0_MAX_OCCURANCES)
     {
         TimerDisable(TIMER0_BASE, TIMER_A);
         Timer0_Occurances = 0;
         count = 0;
     }
}

//*****************************************************************************
void FingerCounting(uint32_t value, uint32_t *F0MotorDuty, uint32_t *F1MotorDuty, uint32_t *F2MotorDuty, uint32_t *F3MotorDuty, uint32_t *F4MotorDuty)
{
    switch (value)
    {
      case 1:   //Number 1
            *F0MotorDuty = 1250;
            *F1MotorDuty = 1250;
            *F2MotorDuty = 6250;
            *F3MotorDuty = 6250;
            *F4MotorDuty = 6250;
       break;

       case 2:   //Number 2
             *F0MotorDuty = 1250;
             *F1MotorDuty = 1250;
             *F2MotorDuty = 1250;
             *F3MotorDuty = 6250;
             *F4MotorDuty = 6250;
        break;

        case 3:   //Number 3
             *F0MotorDuty = 1250;
             *F1MotorDuty = 1250;
             *F2MotorDuty = 1250;
             *F3MotorDuty = 1250;
             *F4MotorDuty = 6250;
         break;

         case 4:   //Number 4
              *F0MotorDuty = 1250;
              *F1MotorDuty = 1250;
              *F2MotorDuty = 1250;
              *F3MotorDuty = 1250;
              *F4MotorDuty = 1250;
         break;

         case 5:  //Open Hand/Paper/Number 5
              *F0MotorDuty = 6250;
              *F1MotorDuty = 1250;
              *F2MotorDuty = 1250;
              *F3MotorDuty = 1250;
              *F4MotorDuty = 1250;
          break;
    }
}
//*****************************************************************************
void CommunicationPinSet(uint32_t gesture_num)
{
    //COMM_0
    if((gesture_num/8) == 1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_0, 255);
        gesture_num -= 8;
        c0 = 1;
    }
    else
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_0, 0);
        c0 = 0;
    }

    //COMM_1
    if((gesture_num/4) == 1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_1, 255);
        gesture_num -= 4;
        c1 = 1;
    }
    else
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_1, 0);
        c1 = 0;
    }

    //COMM_2
    if((gesture_num/2) == 1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_2, 255);
        gesture_num -= 2;
        c2 = 1;
    }
    else
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_2, 0);
        c2 = 0;
    }

    //COMM_3
    if(gesture_num == 1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_3, 255);
        c3 = 1;
    }
    else
    {
        GPIOPinWrite(GPIO_PORTC_BASE, COMM_3, 0);
        c3 = 0;
    }
}

message.txt
31 KB

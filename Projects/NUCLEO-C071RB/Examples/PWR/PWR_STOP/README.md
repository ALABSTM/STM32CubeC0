## <b>PWR_STOP Example Description</b>

This example shows how to enter Stop mode and wake up from this mode using 
an interrupt.

In the associated software, the system clock is set to 48 MHz, an EXTI line
is connected to the user button through PC13 and configured to generate an 
interrupt on falling edge upon key press.
The SysTick is programmed to generate an interrupt each 1 ms and in the SysTick 
interrupt handler, LED1 is toggled in order to indicate whether the MCU is in stop mode 
or run mode.

5 seconds after start-up, the system automatically enters stop mode and LED1 stops toggling.

The User push-button can be pressed at any time to wake-up the system.
The software then comes back in run mode for 5 sec. before automatically entering stop mode again.

Two leds LED1 and LED2 are used to monitor the system state as following:

 - LED2 ON: configuration failed (system will go to an infinite loop)
 - LED1 toggling: system in run mode
 - LED1 off : system in stop mode

These steps are repeated in an infinite loop.

#### <b>Notes</b>

 1. This example can not be used in DEBUG mode due to the fact 
    that the Cortex-M0+ core is no longer clocked during low power mode 
    so debugging features are disabled.

 2. Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
    based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
    a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
    than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
    To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 3. The application needs to ensure that the SysTick time base is always set to 1 millisecond
    to have correct HAL operation.

### <b>Keywords</b>

Power, PWR, Stop mode, Interrupt, EXTI, Wakeup, Low Power, External reset

### <b>Directory contents</b>

  - PWR/PWR_STOP/Inc/stm32c0xx_conf.h         HAL Configuration file
  - PWR/PWR_STOP/Inc/stm32c0xx_it.h           Header for stm32c0xx_it.c
  - PWR/PWR_STOP/Inc/main.h                   Header file for main.c
  - PWR/PWR_STOP/Src/system_stm32c0xx.c       STM32C0xx system clock configuration file
  - PWR/PWR_STOP/Src/stm32c0xx_it.c           Interrupt handlers
  - PWR/PWR_STOP/Src/main.c                   Main program
  - PWR/PWR_STOP/Src/stm32c0xx_hal_msp.c      HAL MSP module

### <b>Hardware and Software environment</b> 
  - This example runs on STM32C0xx devices

  - This example has been tested with STMicroelectronics NUCLEO-C071RB
    board and can be easily tailored to any other supported device
    and development board.

  - NUCLEO-C071RB set-up:
    - Use LED1 and LED2 connected respectively to PA.05 and PC.09 pins
    - User push-button connected to pin PC.13 (EXTI_Line13)

    
### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


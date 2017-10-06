# Button Interrupt

## Purpose
To use a button to cause an interrupt and blink an LED.

## Theory

An interrupt is the opposite of polling, where the processor is constantly searching for the input. An interrupt allows the processor to remain in standby or a low power mode, then when the interrupt is triggered the following code will be implemented.

## Individual Board Features

### MSP430F5529
Every time the variable increments 1000 times the Red LED (P1.0) gets switched. Then when the incremented value reaches 2000 the Green LED (P4.7) blinks and the variable gets set to 0.

### MSP430FR2311
Every time the variable increments 1000 times the Red LED (P1.0) gets switched. Then when the incremented value reaches 2000 the Green LED (2.0) blinks and the variable gets set to 0.

### MSP430FR5994
Every time the variable increments 1000 times the Red LED (P1.0) gets switched. Then when the incremented value reaches 2000 the Green LED (P1.1) blinks and the variable gets set to 0.


### MSP430FR6989
Every time the variable increments 1000 times the Red LED (P1.0) gets switched. Then when the incremented value reaches 2000 the Green LED (P1.7) blinks and the variable gets set to 0.


### MSP4302553
Every time the variable increments 1000 times the Red LED (P1.0) gets switched. Then when the incremented value reaches 2000 the Green LED (P1.6) blinks and the variable gets set to 0.


## Demonstation

<img src= "https://github.com/RU09342/lab-3-interrupts-and-timers-ambrosen8/blob/master/8%20Bit%20LED%20Counter/Assets/8BitCounter.jpg" width="300"/>
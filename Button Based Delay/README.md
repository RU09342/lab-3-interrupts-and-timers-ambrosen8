# Button Based Delay

## Purpose
To blink an LED by a various delays that depend on the length of which a button is pressed down
## Theory
The longer the button on the board is the faster the LED will blink. This works by when the button is pressed an interrupt occurs which starts a timer. Then when the button is released the timer stops. The amount of clock cycles is saved and used to divide the previous amount of clock cycles required to blink the LED causing the period to shorten. Some of the following boards also implement a reset feature. When a second button is pressed the timer resets to the original speed.
## Individual Board Features

### MSP430F5529
Uses both button P2.1 to act as the button delay while button P1.1 is used as a reset. LED P1.0 is the main LED used for the timer. While LED P4.7 is used to show the status of when the button is incrementing the second timer.

![alt text](https://github.com/RU09342/lab-3-interrupts-and-timers-ambrosen8/blob/master/Button%20Based%20Delay/Assets/BBD.gif)
# LED Blink (STM32F407VET6)

This is a simple LED blink program using STM32 HAL.

## Description
- Two LEDs connected to PA6 and PA7 will toggle every 500 ms.

## How to run
1. Open the project in VS Code.
2. Build the code with your STM32 toolchain.
3. Flash to STM32F407VET6 board.
4. LEDs on PA6 and PA7 will blink.

## Code
```c
while (1)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
    HAL_Delay(500);
}

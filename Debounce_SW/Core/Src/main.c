#include "main.h"

#define SW GPIO_PIN_4   // Button (PE4)
#define D2 GPIO_PIN_6   // LED (PA6)
#define D3 GPIO_PIN_7   // LED (PA7)

static void MX_GPIO_Init(void);

int main(void)
{
    HAL_Init();
    MX_GPIO_Init();

    uint8_t buttonState = 1;
    uint8_t lastReading = 1;
    uint32_t lastDebounceTime = 0;
    uint32_t debounceDelay = 20;

    while (1)
    {
        uint8_t reading = HAL_GPIO_ReadPin(GPIOE, SW);

        if (reading != lastReading) {
            lastDebounceTime = HAL_GetTick();
        }

        if ((HAL_GetTick() - lastDebounceTime) > debounceDelay) {
            if (reading != buttonState) {
                buttonState = reading;
                if (buttonState == 0) {
                    HAL_GPIO_TogglePin(GPIOA, D2);
                    HAL_GPIO_TogglePin(GPIOA, D3);
                }
            }
        }

        lastReading = reading;
    }
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, D2 | D3, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = D2 | D3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SW;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

#include <main.h>

static void SysTick_Init(void);
static void delay(uint32_t ms);
static void MX_GPIO_Init(void);

const uint32_t seg[] = {
   
  0x3F, // 0 
  0x06, // 1 
  0x5B, // 2 
  0x4F, // 3 
  0x66, // 4 
  0x6D, // 5 
  0x7D, // 6 
  0x07, // 7 
  0x7F, // 8 
  0x6F // 9

};



void main(void){

  HAL_Init();
  SysTick_Init();
  MX_GPIO_Init();

  while(1){
    for(uint32_t i = 0; i<10; i++){

      GPIOA->ODR &= ~0xFF;
      GPIOA->ODR |= seg[i];
      delay(100);
    }
  }

}

void SysTick_Init(void){
  SysTick ->LOAD = 64000 - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = 5;

}

void delay(uint32_t ms){
  for (uint32_t i = 0; i < ms; i++)
  {
    while((SysTick->CTRL & (1<<16)) == 0);
  }
  
}


static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                        | GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
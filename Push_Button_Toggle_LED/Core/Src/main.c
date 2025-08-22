#include "main.h"

#define D2 GPIO_PIN_6
#define D3 GPIO_PIN_7

#define K1 GPIO_PIN_3

static void MX_GPIO_Init(void);
static void SysTick_Init(void);

int main(void)
{
  HAL_Init();
  MX_GPIO_Init();
  SysTick_Init();

  while (1)
  {
    if(HAL_GPIO_ReadPin(GPIOE, K1) == 0){
      HAL_GPIO_TogglePin(GPIOA, D2|D3);
      delay(30);
    }
    else{
      HAL_GPIO_WritePin(GPIOA, D2, 1);
      HAL_GPIO_WritePin(GPIOA, D3, 1);
    }

  }

}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();


  GPIO_InitStruct.Pin = K1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = D2|D3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}


void SysTick_Init(void){

  SysTick->LOAD = 168000 - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = 5;


}

void delay(uint32_t ms){

  for(uint32_t i=0; i<ms; i++){
    while((SysTick->CTRL & (1<<16)) == 0);
  }
}


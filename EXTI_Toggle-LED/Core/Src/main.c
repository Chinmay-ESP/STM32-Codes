#include "main.h"

static void MX_GPIO_Init(void);
static void SysTick_Init(void);
void delay(uint32_t ms);
void ext_interrupt(int val);


#define Interrupt GPIO_PIN_4
#define D2 GPIO_PIN_6
#define D3 GPIO_PIN_7

int main(void)
{
  HAL_Init();
  MX_GPIO_Init();
  SysTick_Init();


  while (1)
  {
    int val = 0;
    val = HAL_GPIO_ReadPin(GPIOE, Interrupt);
    ext_interrupt(val);
  }
}


void ext_interrupt(int val){

  if(val == 1){
   HAL_GPIO_TogglePin(GPIOA, D2);
   HAL_GPIO_TogglePin(GPIOA, D3);
   delay(100);
  }
  else{
    HAL_GPIO_WritePin(GPIOA, D2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, D3, GPIO_PIN_SET);
    delay(100);
  }

}

void SysTick_Init(void){
  SysTick->LOAD = 16000 - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = 5;
}

void delay(uint32_t ms){
  for(uint32_t i=0; i<ms; i++){
    while((SysTick->CTRL & (1<<16)) == 0);
  }
}



static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}




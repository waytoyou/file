#include "stm32f10x.h"
 
int i;//123
 
void My_Usart1_Send(char *string){
    while(*string){
        /* ????? USART1 */
        USART_SendData(USART1, (unsigned short int) *string++);
 
        /* ???????? */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}
 
 
int main(){
    /******** ?? USART?GPIO ??? ********/
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
 
    /******** ?? GPIOA?USART1 ? RCC ?? ********/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
 
    /******** ?? PA9 ? Tx ?? ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 
    GPIO_Init(GPIOA, &GPIO_InitStructure); // ??? PA9
 
    /******** ?? PA10 ? Rx ?? ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 
    GPIO_Init(GPIOA, &GPIO_InitStructure); // ??? PA10
 
 
    /******** USART ?????? ********/
 
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
    USART_Init(USART1, &USART_InitStructure); // ??? UART1
 
    USART_Cmd(USART1, ENABLE); // ?? USART1
 
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* ?? USART1 ?? */
    NVIC_EnableIRQ(USART1_IRQn);
 
    while(1){ 
//         for(i = 0; i<5000000; i++); 
//         My_Usart1_Send("Hello Kitty \n"); 
    }
 
}
 
void USART1_IRQHandler(){
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
        // ???? A ??,??? ok ??
        if((char)USART_ReceiveData(USART1) == 'A')
        {
            My_Usart1_Send("ok \n");           
        }
				  else if((char)USART_ReceiveData(USART1) == 'B')
        {
            My_Usart1_Send("fuck \n");           
        }
    }
} 
 

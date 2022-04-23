//#include "stm32f1xx_hal.h"
//#include "tim.h"

//volatile int elapsed = 0;                   //用于判断设置的计数值是否耗尽（向下计数模式），耗尽时，在中断中奖会设置为true
// 
//void set_state(int state)
//{
//    elapsed = state;
//}
// 
//int get_state()
//{
//    return elapsed;
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == TIM2) {
//        set_state(0);
//    }
//}
// 
//void delay_200ns(uint32_t times)
//{
// 
//    __HAL_TIM_SetCounter(&htim2,times); 		//设置计数值
//    set_state(0);                  
//    HAL_TIM_Base_Start_IT(&htim2);          //开启定时器
//    while(get_state() != 0);                //判断计数值是否耗尽
//    HAL_TIM_Base_Stop_IT(&htim2);           //关闭定时器
// 
//}

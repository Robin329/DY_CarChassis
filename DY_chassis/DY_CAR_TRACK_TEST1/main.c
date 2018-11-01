/******************************************************************************
 * MSP432E401Y
 * Description:小车红外循迹    
 * Author: Robin.J
***************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
/* Standard Includes */
#include <common.h>

uint32_t g_ui32SysClock;

int main(void)
{
  /* Configure the system clock for 16 MHz */
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          16000000);
  
    GPIOE_INIT();
    GPT_init();
    IncPIDInit();
    PWM_init(pwm_set,0,pwm_set,0);
 //   uart_init();      //串口初始化
    QEIInit();

    while(1)
    {
        
    }
}
/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/
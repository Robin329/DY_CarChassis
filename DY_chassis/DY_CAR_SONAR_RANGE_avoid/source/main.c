/******************************************************************************
 * MSP432E401Y
 * Description:ͨ����������С�����߲����в��
 * Author: Robin.J
***************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <common.h>
#include <qei.h>
uint32_t g_ui32SysClock;

int main(void)
{
  /* Configure the system clock for 16 MHz */
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          16000000);
    GPT_init();      //��ʱ����ʼ��
    Timer_init();
    IncPIDInit();       //PID������ʼ��
    PWM_init(pwm_set,0,pwm_set,0);//PWM��ʼ��
    uart_init();        //���ڳ�ʼ��
    QEIInit();          //QEI��ʼ��
    
    while(1)
    {
        Sonar_Gen();
    }
}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/
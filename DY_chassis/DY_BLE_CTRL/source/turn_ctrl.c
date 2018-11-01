/******************************************************************************
 * MSP432E401Y
 * Description:����С��ǰ����������ת��ֹͣ 
 * ��1��->ǰ��
 * ��2��->����
 * ��3��->��ת
 * ��4��->��ת
 * ��5��->ֹͣ  
 * ���ţ�
 *        
 * Author: Robin.J
*******************************************************************************/
#include <common.h>
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

int ch_l,ch_r;

void Delay_ms(uint8_t n)
{

  SysCtlDelay((g_ui32SysClock / (1000 * 3)) * n);//delay n ms

}
void Forward()  //ǰ��
{
  
  ch_l = 30;
  ch_r = 30;

}

void Turn_Left()  //��ת
{

  ch_l = 10;
  ch_r = 30;
  
}

void Turn_Right()    //��ת   
{

  ch_l = 30;
  ch_r = 10;

}

void Back()     //����
{
  ch_l = 30;
  ch_r = 30;
}

void Stop()     //ֹͣ
{
  ch_l = 0;
  ch_r = 0;
}
void ControlCar(unsigned char ConType)
{ 
  switch(ConType)
  {
    case 1 ://ǰ��
      Forward();
      PWM_init(pwm_pidl, 0 , pwm_pidr , 0 );
      break;
    case 2 ://����
      Back();
      PWM_init(0 ,pwm_pidl,  0, pwm_pidr);
      break;
    case 3 ://��ת
      Turn_Left();
      PWM_init(0 ,pwm_pidl, pwm_pidr , 0);
      break;
    case 4 ://��ת
      Turn_Right();
      PWM_init(pwm_pidl, 0 , 0 , pwm_pidr);
      break;
    case 5 ://ֹͣ
      Stop();
      PWM_init(0, 0 , 0 , 0);
      break;
    default:
      break;
      
  }
}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/
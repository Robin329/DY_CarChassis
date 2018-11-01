#include <PID.h>
#include <turn_ctrl.h>
#include <PID.h>
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

extern float pwm_pidl;
extern float pwm_pidr;
extern uint32_t g_ui32SysClock; 

void Delay_ms(uint8_t n)
{

  SysCtlDelay((g_ui32SysClock / (1000 * 3)) * n);//delay n ms

}
void Forward()
{
  
  sptr->SetPoint_l = 30;
  sptr->SetPoint_r = 30;

}

void Turn_Left()
{

  sptr->SetPoint_l = 10;
  sptr->SetPoint_r = 30;
  
}

void Turn_Right()
{

  sptr->SetPoint_l = 30;
  sptr->SetPoint_r = 10;

}

void Back()
{
  sptr->SetPoint_l = 30;
  sptr->SetPoint_r = 30;
}

void Stop()
{
  sptr->SetPoint_l = 0;
  sptr->SetPoint_r = 0;
}
void ControlCar(unsigned char ConType)
{ 
  switch(ConType)
  {
    case 1 ://前进
      Forward();
      PWM_init(pwm_pidl, 0 , pwm_pidr , 0 );
      break;
    case 2 ://后退
      Back();
      PWM_init(0 ,pwm_pidl,  0, pwm_pidr);
      break;
    case 3 ://左转
      Turn_Left();
      PWM_init(0 ,pwm_pidl, pwm_pidr , 0);
      break;
    case 4 ://右转
      Turn_Right();
      PWM_init(pwm_pidl, 0 , 0 , pwm_pidr);
      break;
    case 5 ://停止
      Stop();
      PWM_init(0, 0 , 0 , 0);
      break;
    default:
      break;
      
  }
}
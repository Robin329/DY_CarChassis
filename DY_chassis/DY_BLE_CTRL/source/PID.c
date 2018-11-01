/******************************************************************************
 * MSP432E401Y
 * Description:PID������
 * ���ţ�
 *       
 * Author: Robin.J
***************************************************************************/
#include <PID.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"

float iError_l , iIncpid_l; //��ǰ���
float iError_r , iIncpid_r; //��ǰ���

float variable_l;
float variable_r;
extern int ch_l,ch_r;
//extern float ch;
//PID��ʼ��
void IncPIDInit(void)
{
	sptr->SetPoint_l	= 30.0;	
        sptr->SetPoint_r	= 30.0;	        //�趨ֵ

	sptr->LastError_l = 0;		//ǰ1�����ֵ
	sptr->PrevError_l = 0;		//ǰ2�����ֵ
        
        sptr->LastError_r = 0;		//ǰ1�����ֵ
	sptr->PrevError_r = 0;		//ǰ2�����ֵ

	sptr->Proportion_r = 0.4;//0.5;//0.8;		//����
	sptr->Integral_r	 = 0.024;//0.026;//0.15;	//����
	sptr->Derivative_r = 0.0;		//΢��
        
        sptr->Proportion_l = 0.8;		//����
	sptr->Integral_l = 0.15;	//����
	sptr->Derivative_l = 0.0;		//΢��
          
        sptr->A_r = sptr->Proportion_r + sptr->Integral_r + sptr->Derivative_r;
        sptr->B_r = -(2*sptr->Derivative_r + sptr->Proportion_r);
        sptr->C_r = sptr->Derivative_r;
        
        sptr->A_l = sptr->Proportion_l + sptr->Integral_l + sptr->Derivative_l;
        sptr->B_l= -(2*sptr->Derivative_l + sptr->Proportion_l);
        sptr->C_l = sptr->Derivative_l;

	sptr->iError_l = 0;		//��ǰ���
        sptr->iError_r = 0;
        
	sptr->iIncpid_l=0;			//�������
        sptr->iIncpid_r=0;
        
        sptr->limit = 49;

}
/* ����PID����*/
float IncPIDCalc_l(float NextPoint)
{
  if(ch_l != 0){
    sptr->SetPoint_l = ch_r;
    iError_l = sptr->SetPoint_l - NextPoint; //��������
  }else{
    return 0;
  }
  
   // iError_l = sptr->SetPoint_l - NextPoint; //��������
    
   sptr->iIncpid_l =(sptr->A_l * iError_l //E[k]��
             + sptr->B_l * sptr->LastError_l //E[k��1]��
             + sptr->C_l * sptr->PrevError_l); //E[k��2]��
 
   variable_l =iError_l -  sptr->LastError_l;
   
    sptr->PrevError_l = sptr->LastError_l;   //�洢�������´μ���
    sptr->LastError_l = iError_l;
 
/*PWM limiting function, PWM value is 80, minimum is 0
*/
//    if(sptr->iIncpid  >= 0)
//    {
//      if(sptr->iIncpid <= sptr->limit){
//        
//        sptr->iIncpid += (pwm_set*100);
//      }
//      else{
//        sptr->iIncpid = (int)(sptr->limit + pwm_set * 100);
//      }
//    }
//    else if(sptr->iIncpid < 0){
//      
//            if(sptr->iIncpid >= -sptr->limit){
//        
//               sptr->iIncpid += (pwm_set*100);
//              }
//            else{
//            
//              sptr->iIncpid =(int)(pwm_set-sptr->limit);
//            }
//      
//    }
    
        if(sptr->iIncpid_l >= sptr->limit)
    {
      sptr->iIncpid_l = sptr->limit;
    
      }
      else if(sptr->iIncpid_l < -sptr->limit){
        
        sptr->iIncpid_l = -sptr->limit;
      }
      
  return(sptr->iIncpid_l);                         //��������ֵ
    
}

/* ����PID����*/
float IncPIDCalc_r(float NextPoint)
{
    if(ch_r != 0){
    sptr->SetPoint_r = ch_r;
    iError_r = sptr->SetPoint_r - NextPoint; //��������
  }else{
    return 0;
  }
  
   // iError_r = sptr->SetPoint_r - NextPoint; //��������

   sptr->iIncpid_r =(sptr->A_r * iError_r //E[k]��
             + sptr->B_r * sptr->LastError_r //E[k��1]��
             + sptr->C_r * sptr->PrevError_r); //E[k��2]��
   variable_r =iError_r -  sptr->LastError_r;
   
    sptr->PrevError_r = sptr->LastError_r;   //�洢�������´μ���
    sptr->LastError_r = iError_r;
    
    if(sptr->iIncpid_r >= sptr->limit)
    {
      sptr->iIncpid_r = sptr->limit;
    
      }
      else if(sptr->iIncpid_r < -sptr->limit){
        
        sptr->iIncpid_r = -sptr->limit;
      }
      
  return(sptr->iIncpid_r);                         //��������ֵ
    
}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/
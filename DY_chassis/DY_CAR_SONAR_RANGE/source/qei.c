/******************************************************************************
 * MSP432E401Y
 * Description:QEIģ���ʼ��  
 * ���ţ�PL1->�����������ź�1
 *       PL2->�����������ź�2
 * Author: Robin.J
*******************************************************************************/

//QEI0��ʼ��
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
/* Standard Includes */
#include <common.h>


    float pid_l = 0;        //����PID
    float pid_r = 0;        //����PID
    float s_l = 0;      //���ֵ�ǰ�ٶ�ֵ
    float s_r = 0;      //���ֵ�ǰ�ٶ�ֵ
//    uint8_t d;        //ת������
    unsigned long  COUNT = 0;
//    unsigned long  POS = 0;   //����λ��
    
    uint8_t Num = 0;    //��ʱ10ms��1
    float pwm_pidl = 0.5;
    float pwm_pidr = 0.5;

void QEIInit (void)
{
  
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);//ʹ��QEI0����
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);/*enable L port*/
    MAP_IntEnable(INT_GPIOL);
    
    GPIOPinConfigure(GPIO_PL1_PHA0);
    GPIOPinConfigure(GPIO_PL2_PHB0);
    
    
    QEIEnable(QEI0_BASE);//ʹ������������QEI0
    QEIConfigure(QEI0_BASE,(QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET|
    QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP),10000000);//ʹ��A,Bͨ����4�����ؼ���λ��
    
//    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_1,
//    GPIO_STRENGTH_4MA,
//    GPIO_PIN_TYPE_STD);
//    
//    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_2,
//    GPIO_STRENGTH_4MA,
//    GPIO_PIN_TYPE_STD);
//    
//    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_3,
//    GPIO_STRENGTH_4MA,
//    GPIO_PIN_TYPE_STD);
//  
    GPIOPinTypeQEI(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2);//����PL1��PL2ΪPhA1��PhB1
    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 16000000/100);//10ms
    
    //ʹ���ٶȼ��㣬ʹ��QEI
    QEIVelocityEnable(QEI0_BASE);
    QEIEnable(QEI0_BASE);

    //�ٶȼ�ʱ����ʱ���ʱ�����ж�
    QEIIntEnable(QEI0_BASE,QEI_INTTIMER);
    IntEnable(INT_QEI0);

}

void QEI0_IRQHandler(void)
{
      Num++;    
    QEIIntClear(QEI0_BASE, QEI_INTTIMER);
//    POS = QEIPositionGet(QEI0_BASE);
//    d = QEIDirectionGet(QEI0_BASE);
  
    COUNT = QEIVelocityGet(QEI0_BASE);
    s_l = (COUNT*6000)/2024;    //�����ٶȼ��㣨rpm/min��
    s_r = speed;        //�����ٶ�
    
/* ����PID����PWMռ�ձ�*/
    pid_l = IncPIDCalc_l(s_l);  // ��������PID����ֵ
    pid_l *= 0.01;
     if(pid_l == -0.5){
      pwm_pidl = 0;     //���ٶ�Ϊ0ʱPWMռ�ձ�Ϊ0
    }else{
    pwm_pidl += pid_l;
    }   
/* ����PID����PWMռ�ձ�*/    
    
    pid_r = IncPIDCalc_r(s_r);  // ��������PID����ֵ
    pid_r *= 0.01;
    if(pid_r == -0.5){
      pwm_pidr = 0;
    }else{
    pwm_pidr += pid_r;
    }
    
    
    if(pwm_pidl > 0.99){        // �޷�����
    
    pwm_pidl = 0.99;
    
    } 
    if(pwm_pidr > 0.99){
      
      pwm_pidr = 0.99;
      
    }
      
    ControlCar(ch);     //��������
  
//    UARTSend((uint8_t *)"Current Speed: ", 16);

if(!UARTBusy(UART0_BASE))       //���ڷ�������
{
  if(Num == 50)
    {
//      UARTSend((uint8_t *)" Current:", 10);//10 is Decimal
      UARTSend((uint8_t *)" dis:", 10);
      Float2Char(dis,Buffer_Out);
      
//      sprintf(Buffer_Out,"%d",(int)s_r);
//      sprintf(Buffer_Out,"%d",(int)s_l);
      UARTSend((uint8_t *)Buffer_Out, 10);
      
      memset(Buffer_Out,0,sizeof(Buffer_Out));//Empty character array
      memset(Buffer,0,sizeof(Buffer));
      Num = 0;
    }
}
// printf("%d,%d\n",s,pid);
// printf("The Speed is %d .Velocity is %d.Direction is %d.\n",s,COUNT,d);
// printf("%d\n",s);
    COUNT = 0;
    
    
}
/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/

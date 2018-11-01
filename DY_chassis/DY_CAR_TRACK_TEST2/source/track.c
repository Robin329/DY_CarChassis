/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <common.h>

/******************************************************************************
*��������Ӧ������
    OUT1--->PE1
    OUT2--->PE2
    OUT3--->PE3
    OUT4--->PE4
    OUT5--->PE5
 * Description:ѭ������
 * Author: renbin.J
******************************************************************************/
int Data_Sensor[5] = {0};
int Data_Sensor_Buf[5] = {0};

void GPIOE_INIT(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
      while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
      {
      }
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5));
    
    
}

void Track_Hand(void)
{
    Data_Sensor[0] = MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1);//2
    Data_Sensor[1] = MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);//4
    Data_Sensor[2] = MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);//8
    Data_Sensor[3] = MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);//16
    Data_Sensor[4] = MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);//32
    
    for(int i = 0;i < 5;i++){
       
      if(i == 5){
      i = 0;
      }
       if(Data_Sensor[0] == 0 && Data_Sensor[1] == 0 && Data_Sensor[2] == 0&& Data_Sensor[3] == 0&& Data_Sensor[4] == 0)
     {
       
         ControlCar(7);//��ԭ��ת
     } else  {
      if(Data_Sensor[i] == 0){
      
        if(i == 2){
        
          ControlCar(1);//ǰ��
          Data_Sensor_Buf[0] = Data_Sensor[0];
          Data_Sensor_Buf[1] = Data_Sensor[1];
          Data_Sensor_Buf[2] = Data_Sensor[2];
          Data_Sensor_Buf[3] = Data_Sensor[3];
          Data_Sensor_Buf[4] = Data_Sensor[4];
        }
        else if(i == 1){
        
                ControlCar(3);//��ת
                Data_Sensor_Buf[0] = Data_Sensor[0];
                Data_Sensor_Buf[1] = Data_Sensor[1];
                Data_Sensor_Buf[2] = Data_Sensor[2];
                Data_Sensor_Buf[3] = Data_Sensor[3];
                Data_Sensor_Buf[4] = Data_Sensor[4];
              }else if(i == 0){
                      ControlCar(4);//���ת
                      Data_Sensor_Buf[0] = Data_Sensor[0];
                      Data_Sensor_Buf[1] = Data_Sensor[1];
                      Data_Sensor_Buf[2] = Data_Sensor[2];
                      Data_Sensor_Buf[3] = Data_Sensor[3];
                      Data_Sensor_Buf[4] = Data_Sensor[4];
                     }
              else if(i == 3){
                       ControlCar(5);//��ת
                      Data_Sensor_Buf[0] = Data_Sensor[0];
                      Data_Sensor_Buf[1] = Data_Sensor[1];
                      Data_Sensor_Buf[2] = Data_Sensor[2];
                      Data_Sensor_Buf[3] = Data_Sensor[3];
                      Data_Sensor_Buf[4] = Data_Sensor[4];
              }else if(i == 4){
                      ControlCar(6);//�Ҵ�ת
                      Data_Sensor_Buf[0] = Data_Sensor[0];
                      Data_Sensor_Buf[1] = Data_Sensor[1];
                      Data_Sensor_Buf[2] = Data_Sensor[2];
                      Data_Sensor_Buf[3] = Data_Sensor[3];
                      Data_Sensor_Buf[4] = Data_Sensor[4];
              }
            
      }
      else{
          if(Data_Sensor[0] != 0 && Data_Sensor[1] != 0 && Data_Sensor[2] != 0 && Data_Sensor[3] != 0 && Data_Sensor[4] != 0){      
                    for(int i = 0;i < 5;i++){
                      if(i == 5){
                      i = 0;
                      }
                        if(Data_Sensor_Buf[i] == 0){
                        
                          if(i == 2){
                          
                            ControlCar(1);//ǰ��
                          }
                          else if(i == 1){
                          
                                  ControlCar(3);//��ת
                                //  Data_Sensor_Buf[1] = Data_Sensor[1];
                                }else if(i == 0){
                                  do{
                                        ControlCar(4);//���ת
                                  } while(Data_Sensor[0] != 0 && Data_Sensor[1] != 0 && Data_Sensor[2] == 0 && Data_Sensor[3] != 0 && Data_Sensor[4] != 0);
                                     // Data_Sensor_Buf[0] = Data_Sensor[0];
                                       }
                                else if(i == 3){
                                  ControlCar(6);//��ת
                               //  Data_Sensor_Buf[3] = Data_Sensor[3];
                                }else if(i == 4){
                                  do{ControlCar(5);//�Ҵ�ת
                                  }while(Data_Sensor[0] != 0 && Data_Sensor[1] != 0 && Data_Sensor[2] == 0 && Data_Sensor[3] != 0 && Data_Sensor[4] != 0);
                                // Data_Sensor_Buf[4] = Data_Sensor[4];
                                }
                              
                        }
              }
              
            }
        }
    }
            
          }
        
} 
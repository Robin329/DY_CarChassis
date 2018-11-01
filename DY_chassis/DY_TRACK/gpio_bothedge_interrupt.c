/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

extern uint32_t g_ui32SysClock;

uint16_t COUNT = 0;
uint16_t TEMP = 0;

void NMI_Handler(void)
{
    uint32_t getIntStatus;

 
    /* Read the interrupt status from the watchdog timer */
    getIntStatus = MAP_WatchdogIntStatus(WATCHDOG0_BASE, true);

    /* If interrupt status is true then clear the interrupt and toggle the
     * LED GPIO */
     if(getIntStatus)
      {
          MAP_WatchdogIntClear(WATCHDOG0_BASE);
          TEMP++;
          if(TEMP == 5)
          {  
            printf("%ds,%d\n",TEMP,COUNT);
            
            COUNT = 0;
            TEMP =0;
          }
          
        
           
      }
   
}


void GPIOE_IRQHandler(void)
{
    uint32_t getIntStatus;

    /* Get the interrupt status from the GPIO and clear the status */
    getIntStatus = MAP_GPIOIntStatus(GPIO_PORTE_BASE, true);

    if((getIntStatus & GPIO_PIN_0) == GPIO_PIN_0)
    {
        MAP_GPIOIntClear(GPIO_PORTE_BASE, getIntStatus);
        

        /* Toggle the LED based on current state of the pin */
       

  
        if(MAP_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_0) == GPIO_PIN_0)
        {
            
            COUNT++;
            
              
        }
       
      
    }
}

void Watchdog_init(void)
{
    
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0)))
    {
     
    }
    /* Configure the WatchDog to generate an interrupt every 10 millisecond */
    MAP_WatchdogReloadSet(WATCHDOG0_BASE, g_ui32SysClock/100);
    MAP_WatchdogIntTypeSet(WATCHDOG0_BASE, WATCHDOG_INT_TYPE_NMI);
    MAP_WatchdogResetDisable(WATCHDOG0_BASE);
    MAP_WatchdogEnable(WATCHDOG0_BASE);
}
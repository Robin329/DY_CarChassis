#ifndef _PID_H
#define _PID_H


//����PID���ƽṹ��
typedef struct 
{
	float SetPoint_l;
	float SetPoint_r;
        
	float Proportion_r;       //��������Proportional Const
	float Integral_r;         //���ֳ���Integral Const
	float Derivative_r;       //΢�ֳ���Derivative Const
        
        float Proportion_l;       //��������Proportional Const
	float Integral_l;         //���ֳ���Integral Const
	float Derivative_l;       //΢�ֳ���Derivative Const
	
	float iError_l;     //��ǰ���
	float iIncpid_l;    //PID����ֵ
        
        float iError_r;     //��ǰ���
	float iIncpid_r;    //PID����ֵ
        
//        	int iError;     //��ǰ���
//	int iIncpid;    //PID����ֵ
	
        float A_r;
        float B_r;
        float C_r;
        
        float A_l;
        float B_l;
        float C_l;
	float LastError_l;  //Error[-1]
	float PrevError_l;  //Error[-2]
        
        float LastError_r;  //Error[-1]
	float PrevError_r;  //Error[-2]
        
        float limit;
        
	
}PID;
//



//����PIDʵ��
static PID sPID;
static PID *sptr = &sPID;


extern void IncPIDInit(void);
extern float IncPIDCalc_l(float NextPoint);
extern float IncPIDCalc_r(float NextPoint);

#endif
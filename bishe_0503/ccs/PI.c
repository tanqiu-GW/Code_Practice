#include "Device.h"
#include "PI.h"


/***********************函数定义****************************
*说明：
*PID控制器默认为PI调节器
*使用了条件编译进行功能切换：节省计算时间
*在校正PI参数时，使用宏定义将PI_DEBUG设为1
*当参数校正完成后，使用宏定义将PI_DEBUG设为0，同时，在初始化
*时，直接为p->a0,p->a1,p->a2赋值
***********************************************************/
void pi_calc(PI * p)
{
    //使用条件编译进行功能切换
    #if (PI_DEBUG)
    float a0,a1,a2;
    //计算中间变量a0,a1,a2
    a0 = p->Kp+p->Ki*p->T+p->Kd/p->T;
    a1 = p->Kp+2*p->Kd/p->T;
    a2 = p->Kd/p->T;
    //计算PID控制器的输出
    p->Out = p->Out_1+a0*p->Err-a1*p->Err_1+a2*p->Err_2;
    #else
    //计算PID控制器的输出
    p->Out = p->Out_1+p->a0*p->Err-p->a1*p->Err_1+p->a2*p->Err_2;
    #endif

    //输出限幅
    if(p->Out>p->OutMax)
        p->Out = p->OutMax;
    if(p->Out<p->OutMax)
        p->Out = p->OutMin;

    //为下步计算做准备
    p->Out_1 = p->Out;
    p->Err_2 = p->Err_1;
    p->Err_1 = p->Err;
}
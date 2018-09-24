#ifndef PI_H
#define PI_H


//定义PI计算用到的结构体类型
typedef struct
{
    float Ref;              //输入：系统待调节量的给定值
    float Fdb;              //输入：系统待调节量的反馈值
    float Kp;               //参数：比例系数
    float Ki;               //参数：积分系数
    float Kd;               //参数：微分系数
    float T;                //参数：离散化系统的采样周期
    float a0;               //变量：a0
    float a1;               //变量：a1
    float a2;               //变量：a2
    float Err;              //变量：当前的偏差e(k)
    float Err_1;            //历史：前一步的偏差e(k-1)
    float Err_2;            //历史：前前一步的偏差e(k-2)
    float Out;              //输出：PI控制器的输出u(k)
    float Out_1;            //历史：PI控制器前一步的输出u(k-1)
    float OutMax;           //参数：PI控制器的最大输出
    float OutMin;           //参数：PI控制器的最小输出
}PI;

//定义PI控制器的初始值
#define PI_DEFAULTS{    0,0,    \
                        0,0,0,  \
                        0.0002, \
                        0,0,0,  \
                        0,0,0,  \
                        0,0,0,0  }

//条件编译的判别条件
#define PI_DEBUG 1

//函数声明
extern void pi_calc(PI *p);


#endif
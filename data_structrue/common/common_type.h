/*
 * @Description: type.h
 * @Author: gw
 * @Date: 2019-05-12 19:44:02
 * @LastEditors: gw
 * @LastEditTime: 2019-05-29 21:36:00
 */

/* 有关类型名的头文件 */

#ifndef __COMMON_TYPE_H__
#define __COMMON_TYPE_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define X86_DEBUG

/* bool value */
typedef enum tagbool
{
	FALSE = 0,
	TRUE = 1
}Bool;

/* status value */
typedef enum tagstatus
{
	FAILED = -1,
	SUCCESS = 1
}Status;


/* X86，32位编译器下 */
#ifdef X86_DEBUG
typedef char S8;
typedef unsigned char U8;
typedef short int S16;
typedef unsigned short int U16;
typedef int S32;
typedef unsigned int U32;
typedef long int SL32;
typedef unsigned long int UL32;
typedef long long int S64;
typedef unsigned long long int U64;
typedef float F32;
typedef double F64;
#endif

#ifndef X86_DEBUG
/* X64，64位编译器下 */
#ifdef X64_DEBUG
typedef char S8;
typedef unsigned char U8;
typedef short int S16;
typedef unsigned short int U16;
typedef int S32;
typedef unsigned int U32;
typedef long int S64;
typedef unsigned long int U64;
typedef float F32;
typedef double F64;
#endif

#endif




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COMMON_TYPE_H__ */

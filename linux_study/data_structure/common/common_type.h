/* 有关类型名的头文件 */

#ifndef __COMMON_TYPE_H__
#define __COMMON_TYPE_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */



#define X86_DEBUG
//#define X64_DEBUG



/* 类型定义 */
typedef enum tagType
{
	INT = 0,
	CHAR = 1
}Type;

typedef enum tagbool
{
	false = 0,
	true = 1
}bool;

typedef enum tagstatus
{
	success = 0,
	failed = -1
}status;

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
//#else if X64_DEBUG
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



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COMMON_TYPE_H__ */

#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>


typedef unsigned short int uint8_t;
typedef short int int8_t;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint8_t bool;

#define   boolean bool
#define BOOL bool
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;


typedef uint8_t __u8;
typedef uint16_t __u16;

typedef int32_t __s32;
typedef uint32_t __u32;

typedef int8_t  s8;

typedef unsigned char BYTE;
typedef BYTE *PBYTE;
typedef unsigned int WORD;
typedef WORD *PWORD;
typedef unsigned long DWORD;
typedef DWORD *PDWORD;

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef struct timer_t TIMER;


#define FALSE     0
#define TRUE      1
#define false     FALSE
#define true      TRUE

#define code

#define idata
typedef  u8 bit;
// math
#ifndef min
#define min(a,b) (((a)<(b))? (a):(b))
#endif

#ifndef max
#define max(a,b) (((a)>(b))? (a):(b))
#endif


#endif


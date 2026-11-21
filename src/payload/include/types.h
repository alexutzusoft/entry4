#ifndef ENTRY4_TYPES_H
#define ENTRY4_TYPES_H

/* Freestanding PS4 payload. No libc, no system headers. */

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef signed char        s8;
typedef short              s16;
typedef int                s32;
typedef long long          s64;

typedef u64 size_t;

#define NULL ((void *)0)

#endif /* ENTRY4_TYPES_H */

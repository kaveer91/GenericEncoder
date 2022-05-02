#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <stdint.h>
#include <stdlib.h>

typedef bool tBool;

typedef uint8_t tU8;
typedef uint16_t tU16;
typedef uint32_t tU32;
typedef uint64_t tU64;

typedef int8_t tS8;
typedef int16_t tS16;
typedef int32_t tS32;
typedef uint64_t tU64;


typedef size_t tSize_t;

typedef enum 
{
	GE_NO_ERROR = 0,
}tReturnCode;

typedef tReturnCode tResult;
#endif
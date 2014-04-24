#ifndef __DS_TYPES_H__
#define __DS_TYPES_H__

#include <stddef.h>
#include <stdint.h>

/**
 * typedefs
 */
typedef int64_t				s64;
typedef int32_t				s32;
typedef int16_t				s16;
typedef int8_t				s8;
typedef uint64_t			u64;
typedef uint32_t			u32;
typedef uint16_t			u16;
typedef uint8_t				u8;

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

#endif // __DS_TYPES_H__

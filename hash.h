#ifndef __DS_HASH_H__
#define __DS_HASH_H__

#include "types.h"

#define HASH_PRIME_MASK		0xf

// 16 primes picked because only they are big enough 
const static u32 hash_primes[16] = {
	28472401U,
	36525343U,
	49979687U,
	67867967U,
	72315377U,
	93245533U,
	160481183U,
	236887691U,
	443826839U,
	536870923U,
	736887719U,
	895829381U,
	1342342367U,
	2147483659U,
	3737267581U,
	4129478957U,
};

#define GOLDEN_RATIO_PRIME_32			0x9e370001UL // copied from the linux kernel
#define HASH_SHIFT_MASK_32				0x1fUL
#define HASH_SHIFT_MASK_64				0x3fULL

/**
 * Hash 32-bit integers to an integer of the designated bits,
 * copied from linux kernel.
 */
static inline u32 hash_32(u32 val, unsigned int bits)
{
	/* On some cpus multiply is faster, on others gcc will do shifts */
	u32 retval = val * GOLDEN_RATIO_PRIME_32;

	/* High bits are more random, so use them. */
	return retval >> (32 - bits);
}

/**
 * Hash 64-bit integers to an integer of the designated bits,
 * copied from linux kernel.
 */
static inline u64 hash_64(u64 val, unsigned int bits)
{
	u64 retval = val;

	/*  Sigh, gcc can't optimise this alone like it does for 32 bits. */
	u64 n = retval;
	n <<= 18;
	retval -= n;
	n <<= 33;
	retval -= n;
	n <<= 3;
	retval += n;
	n <<= 3;
	retval -= n;
	n <<= 4;
	retval += n;
	n <<= 2;
	retval += n;

	/* High bits are more random, so use them. */
	return retval >> (64 - bits);
}

/**
 * hash an array of unsigned 32-bit integers with a magic randomizer
 */
static inline u64 hashstream_32 (const u32 *s, u32 len, u64 magic)
{
	u64 retval = 0;
	u32 i;

	for (i = 0; i < len; ++i) {
		u16 bits = (u16)((u64)(i * magic) & HASH_SHIFT_MASK_32);
		retval ^= (u64) ((s[i] << (32 - bits)) | (s[i] >> bits)) * hash_primes [i & HASH_PRIME_MASK];
	}
	
	return retval;
}

/**
 * hash an array of unsigned 64-bit integers with a magic randomizer
 */
static inline u64 hashstream_64 (const u64 *s, u32 len, u64 magic)
{
	u64 retval = 0;
	u32 i;

	for (i = 0; i < len; ++i) {
		u16 bits = (u16)((u64)(i * magic) & HASH_SHIFT_MASK_64);
		retval ^= ((s[i] << (64 - bits)) | (s[i] >> bits)) * hash_primes [i & HASH_PRIME_MASK];
	}
	
	return retval;
}

/**
 * hash a byte stream
 */
static inline u64 hashstream_8 (const u8 *s, u32 len) 
{
	u64 retval;
	u32 i;
	u32 size = len / sizeof (u64);
	u32 rem = len % sizeof (u64);
	u8 *p = (u8*) s + size * sizeof (u64);

	retval = hashstream_64 ((u64*) s, size, GOLDEN_RATIO_PRIME_32);

	// XOR the remaining < 64 bits
	for (i = 0; i < rem; ++i)
		retval ^= p[i] << (i << 3 /* size of a byte */);
	return retval;
}

#endif // __DS_HASH_H__

#ifndef __DS_CLASS_H__
#define __DS_CLASS_H__

#include "common.h"
#include <stdarg.h>

// class-as-functions and prototype

typedef struct {
	// constructor and destructor
	void *(*new) ();
	void (*delete) (void *);

	// clone
	void *(*clone) (const void *);

	size_t		size;
} class;

#endif // __DS_CLASS_H__

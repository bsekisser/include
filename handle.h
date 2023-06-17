/* **** */

#include "log.h"

/* **** */

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** */

#undef DEBUG
#define DEBUG(_x) _x 

#ifndef DEBUG
	#define DEBUG(_x)
#endif

#define HANDLE_CALLOC(_h, _nmemb, _size) handle_calloc((void**)_h, _nmemb, _size)
static inline void* handle_calloc(void** h, size_t nmemb, size_t size) {
	ERR_NULL(h);

	if(0 != *h) {
		LOG_ACTION(exit(-1));
	}

	void* p = calloc(nmemb, size);
	*h = p;

	DEBUG(LOG("h = 0x%08" PRIxPTR ", p = 0x%08" PRIxPTR ", nmemb = 0x%08zx, size = 0x%08zx",
		(uintptr_t)h, (uintptr_t)p, nmemb, size));

	return(p);
}

#define HANDLE_MALLOC(_h, _size) handle_malloc((void**)_h, _size)
static inline void* handle_malloc(void** h, size_t size) {
	ERR_NULL(h);

	void* p = malloc(size);
	*h = p;

	return(p);
}

#define HANDLE_FREE(_h) handle_free((void**)_h)
static inline void handle_free(void** h) {
	void* p = h ? *h : 0;
	
	DEBUG(LOG_START("h = 0x%08" PRIxPTR, (uintptr_t)h));
	DEBUG(LOG_END(", p = 0x%08" PRIxPTR, (uintptr_t)p));
	
	if(0 == h)
		LOG_ACTION(return);

	if(0 == p)
		LOG_ACTION(return);

	free(p);
	*h = 0;
}

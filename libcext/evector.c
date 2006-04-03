/* extendible vectors. Icarus Sparry 2006.  Public domain. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cext.h"

void
cext_evector_attach(evector_t *v, void *p)
{
	++v->size;
	if (!(v->data = realloc(v->data, v->size * sizeof(void *)))) {
		fprintf(stderr, "%s\n", "Out of memory in cext_evector_attach\n");
		exit(1);
	}
	v->data[v->size - 1]=p;
}

void
cext_evector_detach(evector_t *v, void *data)
{
	void **p = v->data, **end;
	if (!p) return;
	for(end = p + v->size - 1; p <= end; p++)
		if (*p == data) {
			memmove(p, p + 1, end - (p + 1));
			*end = nil;
			--v->size;
			return;
		}
}
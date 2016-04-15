#include <stdlib.h>
#include <string.h>

#include "mallocs.h"

int mf_malloc(size_t size, void **ptr) {
	if (ptr == NULL) return EINVAL;

	if (size == 0) {
		*ptr = NULL;
		return 0;
	}

	void *res = malloc(size);
	if (res == NULL) return ENOMEM;

	*ptr = res;
	return 0;
}

int mf_calloc(size_t size, void **ptr) {
	if (ptr == NULL) return EINVAL;

	if (size == 0) {
		*ptr = NULL;
		return 0;
	}

	void *res = malloc(size);
	if (res == NULL) return ENOMEM;

	memset(res, 0, size);

	*ptr = res;
	return 0;
}

int mf_realloc(size_t size, void **ptr) {
	if (ptr == NULL) return EINVAL;

	if (size == 0) {
		*ptr = NULL;
		return 0;
	}

	void *res = realloc(*ptr, size);
	if (res == NULL) return ENOMEM;

	*ptr = res;
	return 0;
}

int mf_free(size_t size, void **ptr) {
	if (ptr == NULL) return EINVAL;

	free(*ptr);
	*ptr = NULL;
	return 0;
}
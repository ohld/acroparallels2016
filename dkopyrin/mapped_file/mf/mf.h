#ifndef __MF_H_
#define __MF_H_
#include "../chunk_manager/chunk_manager.h"
#include <stddef.h>

//TODO: change to correct datatypes
struct _mf {
	int fd;
	struct chunk_manager cm;
	long int offset;
	long int size;
	int flags;
};

struct _mf* _mf_open(const char *name, int flags, ...);
void _mf_close(struct _mf *mf);

//TODO: Make seek look like lseek
//TODO: Make offset be off_t
int _mf_seek(struct _mf *mf, long int offset);
long int _mf_tell(struct _mf *mf);
ssize_t _mf_read(struct _mf *mf, void *buf, size_t nbyte);
ssize_t _mf_write(struct _mf *mf, const void *buf, size_t nbyte);

#endif

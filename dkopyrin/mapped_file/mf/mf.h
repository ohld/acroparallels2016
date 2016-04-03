#ifndef __MF_H_
#define __MF_H_
#include "../chunk_manager/chunk_manager.h"
#include <stddef.h>

struct mf {
	int fd;
	struct chunk_manager cm;
	long int offset;
	long int size;
	int flags;
};

struct mf* mf_open(const char *name, int flags, ...);
void mf_close(struct mf *mf);

//TODO: Make seek look like lseek
int mf_seek(struct mf *mf, long int offset);
long int mf_tell(struct mf *mf);
ssize_t mf_read(struct mf *mf, void *buf, size_t nbyte);
ssize_t mf_write(struct mf *mf, void *buf, size_t nbyte);

#endif

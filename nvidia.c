#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "nvidia.h"

#define NVIDIA_SYSFS_PATH "/sys/module/nvidia/version"

// read a small file in a newly allocated null terminated buffer
static int read_small_file(const char *path, char **outBuf) {
	*outBuf = NULL;

	int fd = open(path, O_RDONLY);
	if (fd < 0) {
		// Could not open file
		return -1;
	}

	struct stat st;
	if (fstat(fd, &st) < 0) {
		close(fd);
		return -1;
	}

	// We only care about reasonably small files (<=128 bytes).
	if (st.st_size <= 0 || st.st_size > 128) {
		close(fd);
		return -1;
	}

	// Allocate enough space for the file content plus a null terminator.
	char *buf = malloc(st.st_size + 1);
	if (!buf) {
		close(fd);
		return -1;
	}

	ssize_t bytesRead = read(fd, buf, st.st_size);
	close(fd);

	if (bytesRead < 0) {
		free(buf);
		return -1;
	}

	// Null-terminate the buffer
	buf[bytesRead] = '\0';
	*outBuf = buf;

	return 0; // Success
}

const char* get_nvidia_version(void) {
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	static char *cached_version = NULL;
	static int initialized = 0;

	pthread_mutex_lock(&lock);

	if (!initialized) {
		initialized = 1;

		if (read_small_file(NVIDIA_SYSFS_PATH, &cached_version) == 0) {
			cached_version[strcspn(cached_version, "\n")] = '\0';
		}
	}

	pthread_mutex_unlock(&lock);

	return cached_version;
}

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lists.h"

static void* (*real_dlopen)(const char *filename, int flag) = NULL;

void *dlopen_cuda(const char *filename, int flag) {
	char tmpbuf[PATH_MAX];

	// attempt to open filename in one of our available candidate paths
	for(int i = 0; i < sizeof(cuda_candidate_paths)/sizeof(char*); i++) {
		const char *cur = cuda_candidate_paths[i];
		tmpbuf[0] = 0;
		if (cur[0] != '/') {
			// relative path
			char *cuda_home = getenv("CUDA_HOME");
			if (cuda_home == NULL) cuda_home = "/opt/cuda"; // default path
			strncpy(tmpbuf, cuda_home, PATH_MAX-1);
			strncat(tmpbuf, "/", PATH_MAX-1);
		}
		strncat(tmpbuf, cur, PATH_MAX-1); // always ends with a /
		strncat(tmpbuf, filename, PATH_MAX-1);

		// ok we got our full path, let's attempt to dlopen it
		void *res = real_dlopen(tmpbuf, flag);
		if (res != NULL) {
			if (getenv("CUDAPRELOAD_DEBUG") != NULL) {
				printf("opened %s for lib %s\n", tmpbuf, filename);
			}
			return res;
		}
	}
	return NULL;
}

void* dlopen(const char *filename, int flag) {
	if (!real_dlopen) {
		real_dlopen = dlsym(RTLD_NEXT, "dlopen");
	}

	if ((filename == NULL) || (filename[0] == '/')) {
		return real_dlopen(filename, flag);
	}

	// check if filename matches any of our cuda_libs
	for(int i = 0; i < sizeof(cuda_libs)/sizeof(char*); i++) {
		if (strcmp(cuda_libs[i], filename) == 0) {
			// it's a match
			void *res = dlopen_cuda(filename, flag);
			if (res != NULL) {
				return res;
			}
			break;
		}
	}

	// Modify the library loading behavior here, if needed
	return real_dlopen(filename, flag);
}

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lists.h"
#include "nvidia.h"

static void* (*real_dlopen)(const char *filename, int flag) = NULL;

void *dlopen_nvidia_driver(const char *filename, int flag) {
	const char *vers = get_nvidia_version();
	if (vers == NULL) {
		// no driver loaded
		return NULL;
	}
	char tmpbuf[PATH_MAX];

	strncpy(tmpbuf, "/pkg/main/x11-drivers.nvidia-drivers.libs.", PATH_MAX-1);
	strncat(tmpbuf, vers, PATH_MAX-1);
	strncat(tmpbuf, "/lib/", PATH_MAX-1);
	strncat(tmpbuf, filename, PATH_MAX-1);

	// ok we got our full path, let's attempt to dlopen it
	void *res = real_dlopen(tmpbuf, flag);
	if (res != NULL) {
		if (getenv("CUDAPRELOAD_DEBUG") != NULL) {
			printf("opened %s for lib %s\n", tmpbuf, filename);
		}
		return res;
	}
	return NULL;
}

void *dlopen_cudnn(const char *filename, int flag) {
	char tmpbuf[PATH_MAX];

	strncpy(tmpbuf, "/pkg/main/dev-libs.cudnn.libs/lib/", PATH_MAX-1);
	strncat(tmpbuf, filename, PATH_MAX-1);

	// ok we got our full path, let's attempt to dlopen it
	void *res = real_dlopen(tmpbuf, flag);
	if (res != NULL) {
		if (getenv("CUDAPRELOAD_DEBUG") != NULL) {
			printf("opened %s for lib %s\n", tmpbuf, filename);
		}
		return res;
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

	// check if filename matches any cuda_libs
	for(int i = 0; i < sizeof(nvidia_driver_libs)/sizeof(char*); i++) {
		if (strncmp(nvidia_driver_libs[i], filename, strlen(nvidia_driver_libs[i])) == 0) {
			// it's a match
			void *res = dlopen_nvidia_driver(filename, flag);
			if (res != NULL) {
				return res;
			}
			break;
		}
	}
	// check for cudnn
	// TODO if the file ends in .so.8 redirect to cudnn 8 instead of latest
	for(int i = 0; i < sizeof(cudnn_libs_pfx)/sizeof(char*); i++) {
		if (strncmp(cudnn_libs_pfx[i], filename, strlen(cudnn_libs_pfx[i])) == 0) {
			// it's a match
			void *res = dlopen_nvidia_driver(filename, flag);
			if (res != NULL) {
				return res;
			}
			break;
		}
	}

	return real_dlopen(filename, flag);
}

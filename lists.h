#pragma once

static const char *cuda_libs[] = {
	"libcuda.so.1",
	"libcuda.so",
	"libnvcuvid.so.1",
	"libnvcuvid.so",
	"libnvidia-allocator.so.1",
	"libnvidia-allocator.so",
	"libnvidia-cfg.so.1",
	"libnvidia-cfg.so",
	"libnvidia-encode.so.1",
	"libnvidia-encode.so",
	"libnvidia-fbc.so.1",
	"libnvidia-fbc.so",
	"libnvidia-ml.so.1",
	"libnvidia-ml.so",
	"libnvidia-ngx.so.1",
	"libnvidia-ngx.so",
	"libnvidia-opencl.so.1",
	"libnvidia-opencl.so",
	"libnvidia-opticalflow.so.1",
	"libnvidia-opticalflow.so",
	"libnvidia-ptxjitcompiler.so.1",
	"libnvidia-ptxjitcompiler.so",
	"libnvoptix.so.1",
	"libnvoptix.so",
};

static const char *cuda_candidate_paths[] = {
#ifdef __x86_64__
	"/usr/lib64/",
	"/usr/lib/x86_64-linux-gnu/",
	"/opt/cuda/targets/x86_64-linux/lib/",
	"targets/x86_64-linux/lib/", // relative to CUDA_HOME
#endif
	"/usr/lib/",
};


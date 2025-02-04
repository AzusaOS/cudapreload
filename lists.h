#pragma once

// those are prefixes: we either match as an exact string equality, or a prefix with an extra dot

// nvidia libs found in current driver
// /pkg/main/x11-drivers.nvidia-drivers.libs.(version)/lib
static const char *nvidia_driver_libs[] = {
	"libcudadebugger.so",
	"libcuda.so",
	"libGLESv1_CM_nvidia.so",
	"libGLESv1_CM.so",
	"libGLESv2_nvidia.so",
	"libGLESv2.so",
	"libGL.so",
	"libGLX_nvidia.so",
	"libGLX.so",
	"libEGL_nvidia.so",
	"libEGL.so",
	"libnvcuvid.so",
	"libnvidia-allocator.so",
	"libnvidia-api.so",
	"libnvidia-cfg.so",
	"libnvidia-encode.so",
	"libnvidia-egl-gbm.so",
	"libnvidia-egl-wayland.so",
	"libnvidia-fbc.so",
	"libnvidia-ml.so",
	"libnvidia-ngx.so",
	"libnvidia-nvvm.so",
	"libnvidia-opencl.so",
	"libnvidia-opticalflow.so",
	"libnvidia-ptxjitcompiler.so",
	"libnvoptix.so",
	"libOpenCL.so",
	"libOpenGL.so",
	"libvdpau_nvidia.so",
};

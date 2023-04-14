# cudapreload

Sometimes libcuda is installed in a non-standard path. This project overrides dlopen() to direct attempts to load cuda libraries to the right path using a more complete search than normal dlopen()

The following libs are taken into account:

* `libcuda.so.1`
* `libnvcuvid.so.1`
* `libnvidia-allocator.so.1`
* `libnvidia-cfg.so.1`
* `libnvidia-encode.so.1`
* `libnvidia-fbc.so.1`
* `libnvidia-ml.so.1`
* `libnvidia-ngx.so.1`
* `libnvidia-opencl.so.1`
* `libnvidia-opticalflow.so.1`
* `libnvidia-ptxjitcompiler.so.1`
* `libnvoptix.so.1`
* `vdpau/libvdpau_nvidia.so.1` ?

## Usage

	LD_PRELOAD=/tmp/cudapreload.so CUDAPRELOAD_DEBUG=1 TORCH_NVFUSER_LIBRARY_PATH=/.../site-packages/torch/lib/ python3 -c 'import torch; print(torch.cuda.is_available())'


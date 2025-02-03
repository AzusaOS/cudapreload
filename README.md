# cudapreload

This library will allow most tools (torch, etc) needing access to nvidia drivers to work fine. This will analyze the currently loaded nvidia kernel driver and direct dlopen() calls to the right libraries, meaning that even if you upgraded recently but still have an old kernel driver loaded it will still work fine.

Additionally, cudnn libs will also be loaded from cudnn.


## Usage

	LD_PRELOAD=/tmp/cudapreload.so CUDAPRELOAD_DEBUG=1 TORCH_NVFUSER_LIBRARY_PATH=/.../site-packages/torch/lib/ python3 -c 'import torch; print(torch.cuda.is_available())'


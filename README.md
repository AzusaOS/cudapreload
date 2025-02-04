# cudapreload

This library will allow most tools (torch, etc) needing access to nvidia drivers to work fine. This will analyze the currently loaded nvidia kernel driver and direct dlopen() calls to the right libraries, meaning that even if you upgraded recently but still have an old kernel driver loaded it will still work fine.

## Usage

For example with an empty venv

    $ /pkg/main/dev-lang.python.core/bin/python -m venv test
    $ cd test
    $ . bin/activate
    $ pip install torch numpy
    [...]
    $ python -c 'import torch; print(torch.cuda.is_available())'
    False
    $ LD_PRELOAD=/pkg/main/sys-libs.cudapreload.dev/lib64/cudapreload.so python -c 'import torch; print(torch.cuda.is_available())'
    True


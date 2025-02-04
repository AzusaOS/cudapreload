#!/bin/make

OBJECTS=cudapreload.o nvidia.o
TARGET=cudapreload.so

# for make install
PREFIX=/usr/local
LIBDIR=lib
DESTDIR=
CC=gcc
CFLAGS=-Wall -pipe -fPIC

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared -fPIC -std=gnu17 -Wall -pipe -o $@ $^ -ldl

install: $(TARGET)
	install -D -t "$(DESTDIR)$(PREFIX)/$(LIBDIR)" $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS)

test: $(TARGET)
	LD_PRELOAD=$(PWD)/$(TARGET) CUDAPRELOAD_DEBUG=1 /pkg/main/dev-lang.python.core/bin/python -c 'import torch; print(torch.cuda.is_available())'

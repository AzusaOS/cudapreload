#!/bin/make

OBJECTS=cudapreload.o nvidia.o
TARGET=cudapreload.so

# for make install
PREFIX?=/usr/local
LIBDIR?=lib
DESTDIR?=
CC?=gcc
CFLAGS=-Wall -pipe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared -fPIC -std=gnu17 -Wall -pipe -o $@ $< -ldl

install: $(TARGET)
	install -D -t "$(DESTDIR)$(PREFIX)/$(LIBDIR)" $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS)

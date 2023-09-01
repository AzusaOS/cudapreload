#!/bin/make

SOURCE=cudapreload.c
TARGET=cudapreload.so

# for make install
PREFIX?=/usr/local
LIBDIR?=lib
DESTDIR?=
CC?=gcc

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -shared -fPIC -std=gnu17 -Wall -pipe -o $@ $< -ldl

install: $(TARGET)
	install -D -t "$(DESTDIR)$(PREFIX)/$(LIBDIR)" $(TARGET)

clean:
	$(RM) $(TARGET)

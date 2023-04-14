#!/bin/make

SOURCE=cudapreload.c
TARGET=cudapreload.so

# for make install
PREFIX=/usr/local
LIBDIR=lib
DESTDIR=

all: $(TARGET)

$(TARGET): $(SOURCE)
	gcc -shared -fPIC -std=gnu17 -Wall -pipe -o $@ $< -ldl

install: $(TARGET)
	install -D -t "${DESTDIR}${PREFIX}/${LIBDIR}" $(TARGET)

clean:
	$(RM) $(TARGET)

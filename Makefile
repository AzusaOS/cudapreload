#!/bin/make

SOURCE=dlopen_overload.c
TARGET=cudapreload.so

all: $(TARGET)

$(TARGET): $(SOURCE)
	gcc -shared -fPIC -std=gnu17 -Wall -pipe -o $@ $< -ldl

clean:
	$(RM) $(TARGET)

CFLAGS :=-m32 -I. -shared -fPIC -rdynamic -std=gnu11 -fno-omit-frame-pointer -Og -g -Wall -fdiagnostics-color=always -Wno-unused-variable -Wno-unused-function
LDFLAGS:=-Wl,-z,defs -ldl -lbsd -lelf -Wl,-E libiberty.a

SOURCES:=$(shell find . -follow -type f -name '*.c' | grep -v obsolete)
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))
HEADERS:=$(shell find . -follow -type f -name '*.h' | grep -v obsolete)

.PHONY: all clean
all: libtf2mod.so
clean:
	rm -f libtf2mod.so $(shell find . -iname '*.o')

libtf2mod.so: $(OBJECTS) Makefile
	gcc $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c $(HEADERS) Makefile
	gcc $(CFLAGS) -o $@ -c $<

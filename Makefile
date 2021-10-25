cc    = gcc
wincc = x86_64-w64-mingw32-gcc
src   = src/main.c
hdr   = src/colour.h
out   = bin/specfetch
flags = -s -O3 -I/usr/include/libcpuid -lcpuid -Wall

build-linux: $(src) $(hdr)
	$(cc) $(src) $(flags) -o $(out)

build-windows: $(src) $(hdr)
	$(wincc) $(src) $(flags) -o $(out)
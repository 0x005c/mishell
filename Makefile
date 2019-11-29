CC=gcc
SRCS=src/*.c
IDIR=src/
CFLAGS=-Wall -I$(IDIR) -O2
CFLAGS_D=-g -Wall -I$(IDIR) -O2

all: $(SRCS)
	gcc -o bin/mish $(SRCS) $(CFLAGS)

debug: $(SRCS)
	gcc -o bin/mish $(SRCS) $(CFLAGS_D)

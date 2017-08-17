# Makefile for SpeX NMR Software Suite
# for lib directory
# (c) 1998 by BlazerSoft, Volker M. Goebbels

# Which X related libraries to link
XLIBS = -lfltk -lX11 -lXext

# Which standard c/c+ libraries to link
CLIBS = -lm

# Where do we find the fltk library and it´s include files?
INCDIR = -I/usr/local/include
LIBDIR = -L/usr/local/lib -L.

# Build flags
CFLAGS = -O2 -g
MODFLAGS = -O2 -c

# Best compiler ever! :)
CC = gcc

# strip utility to reduce code size
STRIP = strip

# remove utility for clean up
RM = rm -f

# library command
AR = ar cr

# copy command
CP = cp

LIBRARY = libNMR.a

OBJS = utils.o \
       Data.o

all: $(LIBRARY)

test.o: test.C 
	@echo "===== Building module test ===================================="
	@$(CC) $(MODFLAGS) $(INCDIR) test.C

utils.o: utils.C utils.H
	@echo "===== Building module utils ==================================="
	@$(CC) $(MODFLAGS) $(INCDIR) utils.C

Data.o: Data.C Data.H
	@echo "===== Building module Data ===================================="
	@$(CC) $(MODFLAGS) $(INCDIR) Data.C

libNMR.a: $(OBJS)
	@echo "===== Building libNMR ========================================="
	@$(AR) $(LIBRARY) $(OBJS)
	@$(CP) $(LIBRARY) ..

clean:
	@echo "===== Cleaning up ============================================="
	@$(RM) $(OBJS) $(LIBRARY) *~ test.o test-it
	@echo "Done."

test:	$(OBJS) test.o
	@echo "===== Building test item ======================================"
	@$(CC) $(LIBDIR) $(OBJS) $(LIBRARY) test.o -o test-it $(CLIBS) 

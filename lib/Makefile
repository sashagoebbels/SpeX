# Makefile for SpeX NMR Software Suite
# for lib directory
# (c) 1998 by BlazerSoft, Volker M. Goebbels

# Which standard c/c+ libraries to link
CLIBS = -lfftw -lg++ -lm

# Where do we find the fltk library and it´s include files?
INCDIR = -I.
LIBDIR = -L.

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
       Data1D.o \
       Data2D.o

all: $(LIBRARY)

test.o: test.C 
	@echo "===== Building module test ===================================="
	@$(CC) $(MODFLAGS) $(INCDIR) test.C

utils.o: utils.C utils.H
	@echo "===== Building module utils ==================================="
	@$(CC) $(MODFLAGS) $(INCDIR) utils.C

Data1D.o: Data1D.C Data1D.H
	@echo "===== Building module Data1D =================================="
	@$(CC) $(MODFLAGS) $(INCDIR) Data1D.C

Data2D.o: Data2D.C Data2D.H
	@echo "===== Building module Data2D =================================="
	@$(CC) $(MODFLAGS) $(INCDIR) Data2D.C

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

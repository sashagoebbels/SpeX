# Makefile for SpeX NMR Software Suite
# for tree directory
# (c) 1998 by BlazerSoft, Volker M. Goebbels

# Which X related libraries to link
XLIBS = -lGLU -lGL -lfltk -lX11 -lXext

# Which standard c/c+ libraries to link
CLIBS = -lm

# Where do we find the fltk library and it´s include files?
INCDIR = -I/usr/local/include -I..
LIBDIR = -L/usr/local/lib -L.

# Build flags
CFLAGS = -O2 -g
MODFLAGS = -O2 -c -g

# Best compiler ever! :)
CC = gcc

# strip utility to reduce code size
STRIP = strip

# remove utility for clean up
RM = rm -f

# copy command
CP = cp

# library command
AR = ar cr

LIBRARY = libTree.a

OBJS = Fl_Node.o \
       Fl_Tree.o \
       Fl_ToggleNode.o \
       Fl_ToggleTree.o 

all: $(LIBRARY)

Fl_Node.o: Fl_Node.C ../FL/Fl_Node.H
	@echo "===== Building module Fl_Node ================================="
	@$(CC) $(MODFLAGS) $(INCDIR) Fl_Node.C

Fl_Tree.o: Fl_Tree.C
	@echo "===== Building module Fl_Tree ================================="
	@$(CC) $(MODFLAGS) $(INCDIR) Fl_Tree.C

Fl_ToggleNode.o: Fl_ToggleNode.C
	@echo "===== Building module Fl_ToggleNode ==========================="
	@$(CC) $(MODFLAGS) $(INCDIR) Fl_ToggleNode.C

Fl_ToggleTree.o: Fl_ToggleTree.C
	@echo "===== Building module Fl_ToggleTree ==========================="
	@$(CC) $(MODFLAGS) $(INCDIR) Fl_ToggleTree.C

libTree.a: $(OBJS)
	@echo "===== Building libTree ========================================"
	@$(AR) $(LIBRARY) $(OBJS)
	@$(CP) $(LIBRARY) ..

clean:
	@echo "===== Cleaning up ============================================="
	@$(RM) $(OBJS) $(LIBRARY) *~
	@echo "Done."

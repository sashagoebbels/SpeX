# Makefile for SpeX NMR Software Suite
# (c) 1998 by BlazerSoft, Volker M. Goebbels
# Developement version for Linux

# Which X related libraries to link
XLIBS = -lg++ -lGL -lfltk -lX11 -lXext

# Which standard c/c+ libraries to link
CLIBS = -lm -lfftw

# Where do we find the fltk library and it´s include files?
INCDIR = -I/usr/local/include -I./FL -I..
LIBDIR = -L/usr/X11R6/lib -L/usr/local/lib -L. -L..

# Build flags
CFLAGS = -O2 -g
MODFLAGS = -O2 -c -g

# the fabulous NMR library :-)=)
NMRLIB = -lNMR

# modified version of the ToggleTree widget, compiled as a library
TREELIB = -lTree

# Best compiler ever! :)
CC = gcc

# strip utility to reduce code size
STRIP = strip

# remove utility for clean up
RM = rm -f

# copy command
CP = cp

SPEX = spex

ALL = $(SPEX)

OBJS =  parse.o \
	main.o \
	preferences.o \
	parampars.o\
	pref_dialog.o \
	StatusBox.o

all: $(ALL)

pref_dialog.o: pref_dialog.C pref_dialog.H
	@echo "===== Building module pref_dialog ============================="
	@$(CC) $(MODFLAGS) $(INCDIR) pref_dialog.C

parse.o: parse.C parse.H
	@echo "===== Building module parse ==================================="
	@$(CC) $(MODFLAGS) $(INCDIR) parse.C

preferences.o: preferences.C preferences.H
	@echo "===== Building module preferences ============================="
	@$(CC) $(MODFLAGS) $(INCDIR) preferences.C

parampars.o: parampars.C parampars.H
	@echo "===== Building module parampars ==============================="
	@$(CC) $(MODFLAGS) $(INCDIR) parampars.C

StatusBox.o: StatusBox.C StatusBox.H
	@echo "===== Building module StatusBox ==============================="
	@$(CC) $(MODFLAGS) $(INCDIR) StatusBox.C

main.o: main.C
	@echo "===== Building module main ===================================="
	@$(CC) $(MODFLAGS) $(INCDIR) main.C

spex: $(OBJS) color_defs.H
	@echo "===== Building SpeX ==========================================="
	@$(CC) $(OBJS) $(TREELIB) $(NMRLIB) $(CFLAGS) $(LIBDIR) -o $(SPEX) $(XLIBS) $(CLIBS)
	@$(CP) $(SPEX) ..

clean:
	@echo "===== Cleaning up ============================================="
	@$(RM) $(OBJS) spex *~
	@echo "Done."

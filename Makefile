# Master Makefile for SpeX NMR Suite

SHELL=/bin/sh

RM = rm -f

DIRS = lib tree src

SPEX = spex

all:
	@for dir in $(DIRS); do\
		echo "===> $$dir";\
		(cd $$dir; $(MAKE));\
	done

clean:
	@for dir in $(DIRS); do\
		echo "===> $$dir";\
		(cd $$dir; $(MAKE) clean);\
	done
	$(RM) libNMR.a libTree.a $(SPEX) *~

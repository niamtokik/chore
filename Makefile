######################################################################
# GNU Makefile
######################################################################
BUILDDIR ?= _build
CC_OPTS += -std=c99 -O2 -Wall -Werror
CC = cc $(CC_OPTS)

help:
	@echo "Usage: make [all|clean]"

all: $(BUILDDIR)/chored

clean:
	-rm $(BUILDDIR)/chored
	-rm $(BUILDDIR)/*.o

OBJECTS = $(BUILDDIR)/chored.o \
          $(BUILDDIR)/chored_lib.o \
          $(BUILDDIR)/chored_jobs.o

$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/chored: $(BUILDDIR) $(OBJECTS)
	$(CC) -static src/main.c  $(BUILDDIR)/*.o -o $@

$(BUILDDIR)/chored.o: $(BUILDDIR)
	$(CC) -c src/chored.c -o $@

$(BUILDDIR)/chored_lib.o: $(BUILDDIR)
	$(CC) -c src/chored_lib.c -o $@

$(BUILDDIR)/chored_jobs.o: $(BUILDDIR)
	$(CC) -c src/chored_jobs.c -o $@

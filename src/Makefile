IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -O2 -g -Wall

ODIR=../obj
LDIR =../lib

LIBS=-lm

_DEPS = index.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = index.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

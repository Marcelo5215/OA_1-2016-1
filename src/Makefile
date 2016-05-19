IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -g

ODIR=../obj
LDIR =../lib

LIBS=-lm

_DEPS = index.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o index.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
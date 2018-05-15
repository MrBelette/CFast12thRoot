CC = gcc

CFLAGS=  -c -Wall -fPIC -O3

BIN = testfast12throot

#  targets
all:$(BIN)

.SUFFIXES:
.SUFFIXES:  .o .C .c

CSRC :=$(wildcard *.c)
CCSRC :=$(wildcard *.C)

COBJ=$(CSRC:.c=.o)
CCOBJ=$(CCSRC:.C=.o)

OBJS_SRC = $(SOBJ) $(CCOBJ) $(COBJ)
OBJS := $(notdir $(OBJS_SRC))

$(BIN):  $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(BIN)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.dat *.o *.dylib  *~ *\#* *.stackdump $(BIN)

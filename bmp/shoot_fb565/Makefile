src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = shootfb
CC = gcc
#CC = arm-linux-gcc

CFLAGS = -Wall -g
LDFLAGS =

all:$(target)

$(target):$(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $^ 

clean:
	@echo "begin removing file: app *.o *~"
	-rm -f shootfb
	-rm -f *.o
	-rm -f *~
	@echo "finished removing files"

.PHONY: clean

# 2010.5.11

src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = main

CC	=	gcc
CFLAGS	=	-Wall	-c	-g
LDFLAGS	=	-Wall	-g

all:	$(target)

$(target):$(obj)
	$(CC)	-o	$@	$^	$(LDFLAGS)

%.o:%.c
	$(CC)	-o	$@	$<	$(CFLAGS)

clean:
	-rm	-f	$(target)
	-rm	-f	$(obj)
	-rm	-f	*~	*~~
.PHONY:	clean

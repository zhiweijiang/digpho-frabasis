# 2010.2.22

#DIR = ./out/
#TAR_DIR = ./out/

src = $(wildcard *.c)
obj = $(patsubst %.c, $(DIR)%.o, $(src))
target =	main 

CC =	gcc
CFLAGS =	-Wall -g -c -I../jpeg-8/ -I../freetype-2.3.11/include
LDFLAGS	=	-Wall -g -L../jpeg-8/.libs -ljpeg 
LDFLAGS +=	-L../freetype-2.3.11/objs/.libs -lfreetype 
LDFLAGS +=	-L. -lsyj

all: $(target)

$(target): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DIR)%.o:%.c
	$(CC) -o $@ $(CFLAGS) $< 

clean:
	-rm -f $(target)
	-rm -f $(obj)
	-rm -f *~

.PHONY: clean
test:
	@echo $(src)
	@echo $(obj)

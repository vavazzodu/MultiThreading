CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fPIC

SRCPATH = ../Source

OBJSRC = $(SRCPATH)/simple_main.c
OBJEXT = .o

LIBSRC = $(SRCPATH)/ThreadWrapper.c
LIBEXT = .so

#built-in implicit rule
OBJOBJS=$(OBJSRC:%.c=%$(OBJEXT))
LIBOBJS=$(LIBSRC:%.c=%$(OBJEXT))

all: target

target: $(OBJOBJS) libthread.so
	$(CC) $(CFLAGS) $(OBJOBJS) -L. -lthread -lpthread -o executable 

libthread.so: $(LIBOBJS)
	$(CC) $(CFLAGS) -shared $(LIBOBJS) -o libthread.so

# $< → input file , $@ → output file
#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCPATH)/*.o executable *.so
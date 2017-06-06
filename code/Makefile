CFLAGS=-Wall -Wextra -ansi -pedantic -O2
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
LIBS=

prot: $(OBJS)
	$(CC) $(CFLAGS) -o prot $(OBJS) $(LIBS)

limpar:
	rm prot *.o

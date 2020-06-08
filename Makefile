CC	= gcc

CFLAGS	= -g -Wall -Werror -std=c99 -Iinclude

all:: hashtable.c
	$(CC) $(CFLAGS) -o hashtable hashtable.c

clean :
	rm -f hashtable *.o 
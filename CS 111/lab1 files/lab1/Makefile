OBJS = pipe.o
CC = gcc

CFLAGS = -std=c17 -Wpedantic -Wall -O2 -pipe -fno-plt
LDFLAGS = -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now

default: pipe

pipe: ${OBJS}
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY: clean

${OBJS}: pipe.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f ${OBJS} pipe

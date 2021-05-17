CC := gcc
CFLAGS := --std=c99 -Wall -Wextra -lm -lSDL2 -ISDL2
HDRS := vector.h draw.h charge.h utils.h main.h

SRCS := main.c vector.c draw.c charge.c utils.c

OBJS := $(SRCS:.c=.o)

EXEC := main
	
home : $(SRCS) $(HDRS) $(OBJS)
	$(CC) $(SRCS) -c
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)
	rm -f $(OBJS)

%.o: %.c $(HDRS)
	$(CC) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS)
.PHONY: clean
CC := gcc

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lm
HDRS := vector.h draw.h charge.h

SRCS := main.c vector.c draw.c charge.c

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
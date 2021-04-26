CC := gcc

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lm -lSDL2_gfx
HDRS := vector.h particle.h

SRCS := main.c

OBJS := $(SRCS:.c=.o)

EXEC := main
	
home : $(SRCS) $(HDRS)
	$(CC) $(SRCS) -c -o $(OBJS)
	$(CC) $(OBJS) $(HDRS) -o $(EXEC) $(CFLAGS)
	rm -f $(OBJS)
clean:
	rm -f $(EXEC) $(OBJS)
.PHONY: clean
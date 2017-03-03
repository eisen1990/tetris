SOURCE=tetris.c
OBJS=runnable

all:
	gcc -o $(OBJS) $(SOURCE)

clean:
	rm -r $(OBJS)

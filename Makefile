Files := $(wildcard Files/*.c)

all:
	gcc $(Files) -lm -o demon -I Headers


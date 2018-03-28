Files := $(wildcard Files/*.c)

all:
	gcc $(Files) -o demon -I Headers


CC = gcc
DEPS = mymalloc.h
OBJ = memgrind.c mymalloc.c

%.o: %.c $(DEPS)
	$(CC) -c $@ $<

mallocExe: $(OBJ)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm mallocExe

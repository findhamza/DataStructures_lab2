CC = gcc
CFLAGS = -I. -lm
DEPS = main.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

multistack: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

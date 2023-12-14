CC = gcc
CFLAGS = -Wall -Werror

# Target: Final executable
a.out: main.o
	$(CC) -o $@ $^

# Compile main.c to create main.o
main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f a.out main.o
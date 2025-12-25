CC := gcc
CFLAGS := -std=c99 -Werror -Wall -Wextra -Wpedantic -g

app.exe: main.o io_manager.o matrix_manager.o print_menu.o matrix_classic.o matrix_csr.o
	$(CC) -o $@ $^

./%.o : ./%.c ./*.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.exe

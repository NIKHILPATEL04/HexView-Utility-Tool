CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS =
EXEC = xd


all:

	clang xd.c -o xd

clean:
	rm -f $(EXEC) *.o

format:
	clang-format -i --style=file *.[ch]

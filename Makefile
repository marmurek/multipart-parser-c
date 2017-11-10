CFLAGS?= -O3

all: multipart_parser.o

multipart_parser.o: multipart_parser.c

%.o: %.c
	${CC} -std=c89 ${CFLAGS} -ansi -pedantic -Wall -fPIC -c $^ -o $@
solib: multipart_parser.o
	${CC} -shared -Wl,-soname,libmultipart.so -o libmultipart.so multipart_parser.o
clean:
	rm -f *.o *.so

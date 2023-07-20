CFLAGS=--std=c18 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC=gcc

all: image_rotate

pixel.o: pixel.c
$(CC) -c $(CFLAGS) $< -o $@

bmp_header.o: bmp_header.c
$(CC) -c $(CFLAGS) $< -o $@

util.o: util.c
$(CC) -c $(CFLAGS) $< -o $@

image.o: image.c
$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
$(CC) -c $(CFLAGS) $< -o $@

rotations: main.o image.o util.o bmp_header.o pixel.o
$(CC) -o image_rotate $^

clean:
rm -f main.o image.o util.o bmp_header.o pixel.o image_rotate
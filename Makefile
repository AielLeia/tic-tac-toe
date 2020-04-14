all: src/main.c
	gcc -std=c99 -o bin/main src/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2

run:
	bin/main.exe
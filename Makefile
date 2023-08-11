CC= gcc
INC_DIR= inc/
DFLAGS=
CFLAGS= -std=c99 -Wall -I$(INC_DIR)
DEPS= menu.h
LIBS =  


program: src/main.c
	$(CC) $(CFLAGS) $? $(LDFLAGS) $(LIBS) src/menu.c src/functionlib.c src/game.c -o bin/$@ 

run:
	bin/program

format:
	clang-format -i src/*.c
	clang-format -i inc/*.h

clean:
	rm bin/program

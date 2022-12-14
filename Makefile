CC= gcc
INC_DIR= inc/
DFLAGS=
CFLAGS= -std=c99 -Wall -I$(INC_DIR)
DEPS= menu.h
LIBS =  


program: src/main.c
	$(CC) $(CFLAGS) $? $(LDFLAGS) $(LIBS) src/menu.c src/functionlib.c src/game.c -o bin/$@ 

clean:
	rm bin/program

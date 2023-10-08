CC= gcc
LD= gcc

CFLAGS= -std=c99 -Wall -g
INC_DIR= inc/
DFLAGS=
LIBS =  

BIN_FILE = bin/program
BUILD_DIR = build/

all: $(BUILD_DIR)main.o $(BUILD_DIR)menu.o $(BUILD_DIR)game.o $(BUILD_DIR)functionlib.o
	$(CC) $? -o $(BIN_FILE)

$(BUILD_DIR)main.o: src/main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

$(BUILD_DIR)menu.o: src/menu.c
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

$(BUILD_DIR)game.o: src/game.c
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

$(BUILD_DIR)functionlib.o: src/functionlib.c
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

run:
	$(BIN_FILE)

# lay next for changing layout
debug:
	gdb $(BIN_FILE)

format:
	clang-format -i src/*.c
	clang-format -i inc/*.h

clean:
	rm $(BUILD_DIR)*.o
	rm $(BIN_FILE) 

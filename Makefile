CC= gcc
LD= gcc

CFLAGS= -std=c99 -Wall -g
INC_DIR= inc/
LDFLAGS=
LIBS =  

BIN_FILE = 4Wins.elf 
BUILD_DIR = build/

all: $(BUILD_DIR)main.o $(BUILD_DIR)menu.o $(BUILD_DIR)game.o $(BUILD_DIR)functionlib.o
	$(LD) $(LDFLAGS) $? -o $(BIN_FILE)

$(BUILD_DIR)main.o: src/main.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

$(BUILD_DIR)menu.o: src/menu.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

$(BUILD_DIR)game.o: src/game.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

$(BUILD_DIR)functionlib.o: src/functionlib.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBS) -c $? -o $@ 

run:
	./$(BIN_FILE)

# lay next for changing layout
debug:
	gdb $(BIN_FILE)

format:
	clang-format -i src/*.c
	clang-format -i inc/*.h

clean:
	rm -f $(BUILD_DIR)*.o
	rm -f $(BIN_FILE) 

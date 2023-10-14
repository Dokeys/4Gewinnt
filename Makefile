CC= gcc
LD= gcc

CFLAGS= -std=c99 -Wall -g
INC_DIR= inc/
LDFLAGS=
LIBS =

BIN_FILE = 4Wins.elf 
BUILD_DIR = build/

all: pre_build build_program

pre_build: create_folders

build_program: $(BIN_FILE)

create_folders:
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi

$(BIN_FILE): $(BUILD_DIR)main.o $(BUILD_DIR)menu.o $(BUILD_DIR)game.o $(BUILD_DIR)functionlib.o
	$(LD) $(LIBS) $(LDFLAGS) $^ -o $(BIN_FILE)

$(BUILD_DIR)main.o: src/main.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $? -o $@ 

$(BUILD_DIR)menu.o: src/menu.c inc/menu.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ 

$(BUILD_DIR)game.o: src/game.c inc/game.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ 

$(BUILD_DIR)functionlib.o: src/functionlib.c inc/functionlib.h
	@echo 'test = $<'
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ 

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

CC= gcc
LD= gcc

CFLAGS= -std=c99 -Wall -g
LDFLAGS=
LIBS =

MODULES = menu game functionlib
MODULES_DIR = $(addprefix src/,$(MODULES))
INCLUDES = $(addprefix -I,$(MODULES_DIR))
BIN_FILE = 4Wins.elf 
BUILD_DIR = build/
OBJECT_FILES = $(BUILD_DIR)main.o $(addsuffix .o, $(addprefix $(BUILD_DIR),$(MODULES)))

all: pre_build build_program

pre_build: create_folders

build_program: $(BIN_FILE)

create_folders:
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi

$(BIN_FILE): $(OBJECT_FILES)
	$(LD) $(LIBS) $(LDFLAGS) $^ -o $(BIN_FILE)

$(BUILD_DIR)main.o: src/main.c
	$(CC) $? $(CFLAGS) $(INCLUDES) -c -o $@ 

$(BUILD_DIR)menu.o: src/menu/menu.c src/menu/menu.h
	$(CC) $< $(CFLAGS) $(INCLUDES) -c -o $@ 

$(BUILD_DIR)game.o: src/game/game.c src/game/game.h
	$(CC) $< $(CFLAGS) $(INCLUDES) -c -o $@ 

$(BUILD_DIR)functionlib.o: src/functionlib/functionlib.c src/functionlib/functionlib.h
	$(CC) $< $(CFLAGS) $(INCLUDES) -c -o $@ 

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

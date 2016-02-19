CC := clang

OPT_LVL := -O2

DEPS = ./deps
SRC = ./src
SRC_CORE = ./src/core
SRC_GC = ./src/gc
SRC_LANG = ./src/lang
SRC_LANG_LIST = ./src/lang/List
SRC_LANG_VECTOR = ./src/lang/Vector
SRC_LANG_NUMBERS = ./src/lang/Numbers
SRCS = -I$(DEPS) -I$(SRC) -I$(SRC_CORE) -I$(SRC_GC) -I$(SRC_LANG) -I$(SRC_LANG_LIST) -I$(SRC_LANG_VECTOR) -I$(SRC_LANG_NUMBERS)

C_FLAGS := -ansi $(OPT_LVL) $(SRCS) -Wall -Wno-unused-function


all: install_deps build_test run_test

run_test:
	./test/main

build_test: build_lib.o
	$(CC) $(C_FLAGS) ./test/lib.o ./test/main.c -o ./test/main

build_lib.o:
	$(CC) $(C_FLAGS) -c ./lib.c -o ./test/lib.o

install_deps:
	clib install

clean:
	$(RM) ./test/main **/*.o **/*~
	$(RM) -rf deps

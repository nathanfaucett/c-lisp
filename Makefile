CC := clang

OPT_LVL := -O2

DEPS = ./deps
SRC = ./src
SRC_CORE = ./src/core
SRC_GC = ./src/gc
SRC_LANG = ./src/lang
SRC_LANG_LIST = ./src/lang/List
SRC_LANG_VECTOR = ./src/lang/Vector
SRCS = -I$(DEPS) -I$(SRC) -I$(SRC_CORE) -I$(SRC_GC) -I$(SRC_LANG) -I$(SRC_LANG_LIST)  -I$(SRC_LANG_VECTOR)

C_FLAGS := -ansi $(OPT_LVL) $(SRCS) -Wall -Wno-unused-function


all: install build_test run_test

run_test:
	./test/main

build_test: build_lib.o
	$(CC) $(C_FLAGS) ./test/lib.o ./test/main.c -o ./test/main

build_lib.o:
	$(CC) $(C_FLAGS) -c ./lib.c -o ./test/lib.o

install:
	clib install

clean:
	$(RM) ./test/main **/*.o **/*~
	$(RM) -rf deps

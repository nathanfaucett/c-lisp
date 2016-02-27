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
SRC_LANG_READER = ./src/lang/Reader
SRCS = -I$(DEPS) -I$(SRC) -I$(SRC_CORE) -I$(SRC_GC) -I$(SRC_LANG) -I$(SRC_LANG_LIST) -I$(SRC_LANG_VECTOR) -I$(SRC_LANG_NUMBERS) -I$(SRC_LANG_READER)

C_FLAGS := -ansi $(OPT_LVL) $(SRCS) -Wall -Wno-unused-function


all: install_deps build_test run_test

run_test:
	./test/main

build_test: build_libs
	$(CC) $(C_FLAGS) ./test/string_to_float.o ./test/string_to_int.o ./test/lib.o ./test/main.c -o ./test/main

build_libs:
	$(CC) $(C_FLAGS) -c ./lib.c -o ./test/lib.o
	$(CC) $(C_FLAGS) -c ./deps/string_to_int/lib.c -o ./test/string_to_int.o
	$(CC) $(C_FLAGS) -c ./deps/string_to_float/lib.c -o ./test/string_to_float.o

install_deps:
	clib install

clean:
	$(RM) ./test/main **/*.o **/*~
	$(RM) -rf deps

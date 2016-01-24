COMPILER_C := clang
COMPILER_CPP := clang++

OPT_LVL := -O2

C_FLAGS := -ansi $(OPT_LVL) -Wall -Wno-unused-function
CPP_FLAGS := -ansi $(OPT_LVL) -Wall -Wno-c++11-compat-deprecated-writable-strings -Wno-unused-function


build_simple_c:
	$(COMPILER_C) $(C_FLAGS) ./test/simple.c -o ./test/simple.out

run_simple_c:
	./test/simple.out

simple: build_simple_c run_simple_c

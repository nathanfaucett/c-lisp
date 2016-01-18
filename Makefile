COMPILER_C := clang
COMPILER_CPP := clang++

OPT_LVL := -O2

C_FLAGS := -std=libc -ansi $(OPT_LVL) -Wall -Wno-unused-function
CPP_FLAGS := -stdlib=libc++ -ansi $(OPT_LVL) -Wall -Wno-c++11-compat-deprecated-writable-strings -Wno-unused-function


test_c:
	$(COMPILER_C) $(C_FLAGS) ./test/main.c -o ./test/test.out && ./test/test.out

test_cpp:
	$(COMPILER_CPP) $(CPP_FLAGS) ./test/main.cpp -o ./test/test.out && ./test/test.out

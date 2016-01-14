COMPILER_C := clang
COMPILER_CPP := clang++

OPT_LVL := -O2

C_FLAGS := -std=libc -ansi $(OPT_LVL) -Wall -Wno-unused-function
CPP_FLAGS := -stdlib=libc++ -ansi $(OPT_LVL) -Wall -Wno-c++11-compat-deprecated-writable-strings -Wno-unused-function


test_c:
	$(COMPILER_C) $(C_FLAGS) ./test/test.c -o ./test/a.out && ./test/a.out

test_cpp:
	$(COMPILER_CPP) $(CPP_FLAGS) ./test/test.cpp -o ./test/a.out && ./test/a.out

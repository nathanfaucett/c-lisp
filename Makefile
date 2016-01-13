COMPILER_C := clang
COMPILER_CPP := clang++

C_FLAGS := -stdlib=libc -std=c99 -Wall
CPP_FLAGS := -stdlib=libc++ -std=c++98 -Wno-c++11-compat-deprecated-writable-strings -Wall


test_c:
	$(COMPILER_C) $(C_FLAGS) ./test/test.c -o ./test/a.out && ./test/a.out

test_cpp:
	$(COMPILER_CPP) $(CPP_FLAGS) ./test/test.cpp -o ./test/a.out && ./test/a.out

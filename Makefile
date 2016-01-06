CXX = g++
CXX_FLAGS = -Wall -std=c++0x

LIB_DIR = -L/usr/lib
INC_DIR = -I/usr/include


build_test:
	$(CXX) ./test/main.cpp $(CXX_FLAGS) -o ./test/a.out && ./test/a.out

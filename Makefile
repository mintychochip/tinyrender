CXX = g++
CFLAGS = -g -Wall -Wextra -no-pie -O0  # Add -pg for profiling, -O0 to disable optimization
SRC = image.cpp main.cpp model.cpp
OBJ = ${SRC:.cpp=.o}

all: tiny

tiny: main.cpp image.cpp model.cpp
	g++ main.cpp image.cpp model.cpp -ggdb -g -pg -O0 -o tiny

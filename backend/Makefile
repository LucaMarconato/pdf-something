CC = clang++
FLAGS = -g -std=c++17 -Wall -Wextra -O0 #debug

SRCS = $(wildcard *.cpp)
# INCLUDES = -I/usr/local/Cellar/boost/1.66.0/include/
# LIBS = -L/usr/local/Cellar/boost/1.66.0/lib/
OBJS = $(SRCS:.cpp=.o)
OUT = libbackend

$(OUT): $(OBJS)
	ar rcs $(OUT).a $^
# libtool -static -o $(OUT).a $^ #other possibilty

%.o: %.cpp Makefile
	$(CC) $(FLAGS) -c $< -o $@

# if needed to build for other architectures
# %.o: %.cpp Makefile clean
# 	$(CC) $(FLAGS) -c $< -o $@ -arch x86_64 -arch i386

.PHONY: clean all

clean: 
	rm -rf $(OUT).a *.o

all: $(OUT)

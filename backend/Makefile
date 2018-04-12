CC = clang++
FLAGS = -g -std=c++14 -Wall -Wextra -O0 #debug
# FLAGS = -std=c++14 -Ofast # release

SRCS = $(wildcard *.cpp)
INCLUDES = 
LIBS = 
OBJS = $(SRCS:.cpp=.o)
OUT = libbackend

$(OUT): $(OBJS)
	ar rcs $(OUT).a $^
# libtool -static -o $(OUT).a $^ #other possibilty

$(OBJS): $(SRCS) Makefile clean
	$(CC) $(SCRS) $(FLAGS) -c $< -o $@ -arch x86_64 -arch i386

.PHONY: clean

clean:
	rm -rf *.o $(OUT).a

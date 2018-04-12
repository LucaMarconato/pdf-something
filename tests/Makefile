CC = g++
# debug
FLAGS = -g -std=c++14 -Wall -O0
# release
# FLAGS = -std=c++14 -Ofast

GTEST_ROOT = ./../../googletest

SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.h)

INCLUDE = -I$(GTEST_ROOT)/include
LIBS = ../../backend
OBJS = $(SRCS:.cpp=.o)
OUT = canonical-frontend

$(OBJS): $(SRCS) $(HDRS)
	$(CC) $(SCRS) $(HDRS) $(FLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(OBJS) $(INCLUDE) $(LIBS) -lbackend

.PHONY: clean run

clean:
	rm -rf $(OUT) *.o

run:
	./$(OUT)

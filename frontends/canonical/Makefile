CC = clang++
FLAGS = -g -std=c++14 -Wall -O0 # debug
# FLAGS = -std=c++14 -Ofast # release

SRCS = $(wildcard *.cpp)
INCLUDES = -I../../backend
LIBS = -L../../backend
OBJS = $(SRCS:.cpp=.o)
OUT = canonical-frontend

$(OUT): $(OBJS)
	$(CC) $(FLAGS) -o $(OUT) $(OBJS) $(INCLUDES) $(LIBS) -lbackend

$(OBJS): $(SRCS) Makefile
	$(CC) $(SCRS) $(FLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean run

clean:
	rm -rf $(OUT) *.o

run:
	./$(OUT)

CC = clang++
FLAGS = -g -std=c++14 -Wall -O0 # debug
# FLAGS = -std=c++14 -Ofast # release

SRCS = $(wildcard *.cpp)
INCLUDES = -I../../backend
LIBS = -L../../backend
OBJS = $(SRCS:.cpp=.o)
OUT = canonical-frontend

$(OUT): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUT) $(INCLUDES) $(LIBS) -lbackend 

%.o: %.cpp Makefile ../../backend/libbackend.a
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean run

clean:
	rm -rf $(OUT) *.o

#build and run are used in my emacs configuration
build: $(OUT)

run:
	./$(OUT)

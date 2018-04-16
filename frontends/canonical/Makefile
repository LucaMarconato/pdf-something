CC = clang++
FLAGS = -g -std=c++17 -Wall -O0 # debug

SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)
BACKEND_SRCS = $(wildcard ../../backend/*.cpp)
BACKEND_MAKEFILE = ../../backend/Makefile
INCLUDES = -I../../backend
LIBS = -L../../backend
OBJS = $(SRCS:.cpp=.o)
OUT = canonical-frontend

$(OUT): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUT) $(INCLUDES) $(LIBS) -lbackend 

%.o: %.cpp Makefile ../../backend/libbackend.a make_backend
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

make_backend: $(BACKEND_SRCS) $(BACKEND_MAKEFILE)
	make -C ../../backend/

.PHONY: clean run

clean:
	rm -rf $(OUT) *.o

#build and run are used in my emacs configuration
build: $(OUT)

run:
	./$(OUT)

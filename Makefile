COMPILER = g++ -std=c++11
FLAGS = -Wall
LINKING_FLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system 
ONAME = out
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(OBJ) 
	$(COMPILER) $(OBJ) $(LINKING_FLAGS) -o $(ONAME)
	./$(ONAME)

%.o: %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

.PHONY: clean g
clean:
	rm -f *.o out

g:
	./out

COMPILE_FLAGS = -O2
CPP 		  = g++ $(COMPILE_FLAGS)

SRC = Src/
BIN = Bin/
OBJ = Obj/

all: $(SRC)main.cpp $(SRC)SharedPtr.hpp
	$(CPP) $(SRC)main.cpp -o $(BIN)run

clean:
	-cd Obj; rm *
	-cd Bin; rm *

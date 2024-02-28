COMPILE_FLAGS = -O2
CPP 		  = g++ $(COMPILE_FLAGS)

SRC = Src/
BIN = Bin/
OBJ = Obj/

all: shared_ptr main.cpp
	$(CPP) $(SRC)main.cpp -o $(BIN)run

shared_ptr: $(SRC)SharedPtr.cpp $(SRC)SharedPtr.hpp
	$(CPP) -c $(SRC)SharedPtr.cpp -o $(BIN)SharedPtr.o

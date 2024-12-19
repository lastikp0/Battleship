CXX = g++

INCLUDE_DIR = ../../include/
INCLUDE = $(wildcard $(INCLUDE_DIR)ship/*.h $(INCLUDE_DIR)field/*.h)
CXXFLAGS = -I $(INCLUDE_DIR)ship/ -I $(INCLUDE_DIR)field/ -c

SRC_DIR = ./
SRC = $(wildcard $(SRC_DIR)*.cpp)

BIN_DIR = ../../bin/
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC))

all : $(OBJ)

$(BIN_DIR)%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) $< -o $@
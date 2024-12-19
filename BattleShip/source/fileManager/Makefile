CXX = g++

INCLUDE_DIR = ../../include/
INCLUDE = $(wildcard $(INCLUDE_DIR)*/*.h)
CXXFLAGS = -I $(INCLUDE_DIR)ship/ -I $(INCLUDE_DIR)field/ -I $(INCLUDE_DIR)ability/ -I $(INCLUDE_DIR)participant/ -I $(INCLUDE_DIR)game/ -I $(INCLUDE_DIR)fileManager/  -c

SRC_DIR = ./
SRC = $(wildcard $(SRC_DIR)*.cpp)

BIN_DIR = ../../bin/
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC))

all : $(OBJ)

$(BIN_DIR)%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) $< -o $@
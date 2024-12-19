CXX = g++

INCLUDE_DIR = ../../include/
INCLUDE = $(wildcard $(INCLUDE_DIR)ship/*.h $(INCLUDE_DIR)field/*.h $(INCLUDE_DIR)ability/*.h $(INCLUDE_DIR)participant/*.h $(INCLUDE_DIR)game/*.h)
CXXFLAGS = -I $(INCLUDE_DIR)ship/ -I $(INCLUDE_DIR)field/ -I $(INCLUDE_DIR)ability/ -I $(INCLUDE_DIR)participant/ -I $(INCLUDE_DIR)game/ -c

SRC_DIR = ./
SRC = $(wildcard $(SRC_DIR)*.cpp)

BIN_DIR = ../../bin/
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC))

all : $(OBJ)

$(BIN_DIR)%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) $< -o $@
TARGET = ./main

CXX = g++

INCLUDE_DIR = ./include/
INCLUDE = $(wildcard $(INCLUDE_DIR)*/*.h)
CXXFLAGS = -I $(INCLUDE_DIR)ship/ -I $(INCLUDE_DIR)field/ -I $(INCLUDE_DIR)ability/ -I $(INCLUDE_DIR)participant/ -I $(INCLUDE_DIR)fileManager/ -I $(INCLUDE_DIR)game/

SRC_DIR = ./source/
SRC = $(wildcard $(SRC_DIR)*/*.cpp)

BIN_DIR = ./bin/
OBJ = $(addprefix $(BIN_DIR), $(patsubst %.cpp, %.o, $(notdir $(SRC))))

all : create_bin_dir game file_manager participant ability field ship $(TARGET)

game :
	make -C $(SRC_DIR)game/

file_manager :
	make -C $(SRC_DIR)fileManager/

participant :
	make -C $(SRC_DIR)participant/

ability :
	make -C $(SRC_DIR)ability/

field :
	make -C $(SRC_DIR)field/

ship :
	make -C $(SRC_DIR)ship/

$(BIN_DIR)main.o : $(SRC_DIR)main.cpp $(INCLUDE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJ) $(BIN_DIR)main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

create_bin_dir :
	@mkdir -p $(BIN_DIR)

clean:
	@rm $(TARGET)
	@rm -rf $(BIN_DIR)
	@rm ./save.txt
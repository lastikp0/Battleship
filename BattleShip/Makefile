TARGET = ./main

CXX = g++

INCLUDE_DIR = ./include/
INCLUDE = $(wildcard $(INCLUDE_DIR)*/*.h)
CXXFLAGS = -I $(INCLUDE_DIR)ship/ -I $(INCLUDE_DIR)field/ -I $(INCLUDE_DIR)ability/ -I $(INCLUDE_DIR)participant/ -I $(INCLUDE_DIR)fileManager/ -I $(INCLUDE_DIR)game/ -I $(INCLUDE_DIR)gameRenderer/ -I $(INCLUDE_DIR)gameController/

SRC_DIR = ./source/
SRC = $(wildcard $(SRC_DIR)*/*.cpp)

BIN_DIR = ./bin/
OBJ = $(addprefix $(BIN_DIR), $(patsubst %.cpp, %.o, $(notdir $(SRC))))

all : create_bin_dir ship field ability participant file_manager game game_renderer game_controller $(TARGET)

ship :
	make -C $(SRC_DIR)ship/

field :
	make -C $(SRC_DIR)field/

ability :
	make -C $(SRC_DIR)ability/

participant :
	make -C $(SRC_DIR)participant/

file_manager :
	make -C $(SRC_DIR)fileManager/

game :
	make -C $(SRC_DIR)game/

game_renderer :
	make -C $(SRC_DIR)gameRenderer/

game_controller :
	make -C $(SRC_DIR)gameController/

$(BIN_DIR)main.o : $(SRC_DIR)main.cpp $(INCLUDE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJ) $(BIN_DIR)main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

create_bin_dir :
	@mkdir -p $(BIN_DIR)

clean:
	@rm $(TARGET)
	@rm -rf $(BIN_DIR)
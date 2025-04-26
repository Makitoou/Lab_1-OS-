CXX = g++
CXXFLAGS = -Wall -Wextra -I./src
LDFLAGS = -static -lole32 -loleaut32 -luuid

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLES = $(BIN_DIR)/main $(BIN_DIR)/parent

all: $(EXECUTABLES)

$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/fibonacci.o
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/parent: $(OBJ_DIR)/parent.o $(OBJ_DIR)/fibonacci.o
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $^ -o $@ $(LDFLAGS) -ladvapi32

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rmdir /s /q $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
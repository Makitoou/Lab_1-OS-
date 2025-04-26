# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -I./src
LDFLAGS = -lole32 -loleaut32 -luuid -static

# Директории
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Исходные файлы
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLES = $(BIN_DIR)/main $(BIN_DIR)/parent

# Цели по умолчанию
all: $(EXECUTABLES)

# Сборка main
$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/fibonacci.o
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Сборка parent (требует Windows API)
$(BIN_DIR)/parent: $(OBJ_DIR)/parent.o $(OBJ_DIR)/fibonacci.o
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LDFLAGS) -ladvapi32

# Компиляция всех .cpp в .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
CXX      = g++
CFLAGS   = -Wall -Werror -pedantic
LFLAGS   = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  :=

EXE      := PhotoMagic
TARGET   := $(EXE)

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all clean

all: $(TARGET)

# linking
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CFLAGS) $^ $(LFLAGS) -o $@

# .cpp + .hpp pairs
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp| $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Singleton .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Directories
$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

clean:
	@$(RM) -rvf $(BIN_DIR) $(OBJ_DIR) $(TARGET)

-include $(OBJ:.o=.d)
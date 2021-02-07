CXX       = g++
CFLAGS   = -g -Wall -Werror -pedantic
LFLAGS   = -lboost_unit_test_framework

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

EXE      := boosttest
TARGET   := $(BIN_DIR)/$(EXE)

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
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
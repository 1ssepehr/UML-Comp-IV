CXX      := g++
CXXFLAGS := -Wextra -Werror -pedantic -ggdb -std=c++17 -MMD -MP
LFLAGS   :=

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

EXE      := $(BIN_DIR)/CircBuffer

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all
all: $(EXE)

$(EXE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

.PHONY: clean
clean:
	@$(RM) -rvf $(BIN_DIR) $(OBJ_DIR)

-include $(OBJECTS:%.o=%.d)
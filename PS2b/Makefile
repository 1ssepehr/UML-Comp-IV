CXX      = g++
CXXFLAGS = -Wall -Werror -pedantic -g -std=c++17 -MMD
LFLAGS   = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

EXE      := $(BIN_DIR)/NBody

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all
all: $(EXE)

$(EXE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LFLAGS) -o $@

$(OBJECTS): $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

.PHONY: clean
clean:
	@$(RM) -rvf $(BIN_DIR) $(OBJ_DIR)

-include $(OBJECTS:%.o=%.d)
CXX      := g++
CXXFLAGS := -Wextra -Werror -pedantic -ggdb -std=c++17 -MMD -MP
LFLAGS   := -lsfml-system -lsfml-graphics -lsfml-window

SRC_DIR  := src
OBJ_DIR  := obj
EXE      := PS1b

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all build test clean

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $^ $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

clean:
	@$(RM) -rvf $(EXE) $(TEST) $(OBJ_DIR)

-include $(OBJECTS:%.o=%.d)
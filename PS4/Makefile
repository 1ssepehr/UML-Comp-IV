# (C) Copyright Seyedsepehr Madani, 2021.
# Distributed under MIT license
# Available at https://opensource.org/licenses/MIT.

CXX      := g++
CXXFLAGS := -Wextra -Werror -pedantic -ggdb -std=c++17 -MMD -MP
LFLAGS   := -lboost_unit_test_framework

SRC_DIR  := src
OBJ_DIR  := obj
EXE      := CircBufferTest

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all
all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $^ $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

.PHONY: clean
clean:
	@$(RM) -rvf $(EXE) $(OBJ_DIR)

-include $(OBJECTS:%.o=%.d)
# (C) Copyright Seyedsepehr Madani, 2021.
# Distributed under MIT license
# Available at https://opensource.org/licenses/MIT.

CXX      := g++
CXXFLAGS := -Wextra -Werror -pedantic -ggdb -std=c++17 -MMD -MP
LFLAGS   := -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window
LFLAGS_T := -lboost_unit_test_framework

SRC_DIR  := src
OBJ_DIR  := obj
EXE      := PS4b
TEST     := PS4b_test

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all build test clean
all: build test

build: $(EXE)

test: $(TEST)

$(TEST): $(filter-out $(OBJ_DIR)/KSGuitarSim.o, $(OBJECTS))
	$(CXX) $^ $(LFLAGS_T) -o $@

$(EXE): $(filter-out $(OBJ_DIR)/boosttest.o, $(OBJECTS))
	$(CXX) $^ $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

clean:
	@$(RM) -rvf $(EXE) $(TEST) $(OBJ_DIR)

-include $(OBJECTS:%.o=%.d)
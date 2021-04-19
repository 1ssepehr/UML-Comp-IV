CXX      := g++
CXXFLAGS := -std=c++17 -Wextra -Werror -pedantic -ggdb -MMD -MP
LFLAGS   := -lboost_unit_test_framework

SRC_DIR  := src
OBJ_DIR  := obj

EXE      := PS1a

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all clean
all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $^ $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -pv $@

clean:
	@$(RM) -rvf $(OBJ_DIR) $(EXE)

-include $(OBJECTS:%.o=%.d)
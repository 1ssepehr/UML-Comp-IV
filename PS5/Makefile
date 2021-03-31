CXX      := clang++
CXXFLAGS := -Wextra -Werror -pedantic -ggdb -std=c++17 -MMD -MP
LFLAGS   := -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR  := src
OBJ_DIR  := obj

EXE      := Triangle

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all clean
all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -pv $@

clean:
	@$(RM) -rvf $(OBJ_DIR) $(EXE)

-include $(OBJECTS:%.o=%.d)
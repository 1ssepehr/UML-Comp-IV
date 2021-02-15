CXX      = g++
CFLAGS   = -Wall -Werror -pedantic
LFLAGS   = -lsfml-graphics -lsfml-window -lsfml-system
TEST_FLAGS = $(LFLAGS)  -lboost_unit_test_framework

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin
TEST_DIR := test

EXE      := $(BIN_DIR)/PhotoMagic
TEST     := $(BIN_DIR)/boost_test

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

TEST_SRC := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRC))  $(OBJECTS)
TEST_OBJ := $(filter-out $(OBJ_DIR)/main.o, $(TEST_OBJ))

.PHONY: all clean

# all
all: $(EXE)

# test files
test: $(TEST)

# linking
$(EXE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CFLAGS) $^ $(LFLAGS) -o $@

# test linking
$(TEST): $(TEST_OBJ) | $(BIN_DIR)
	$(CXX) $(CFLAGS) $^ $(TEST_FLAGS) -o $@

# .cpp + .hpp pairs
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# test sources
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Singleton .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Directories
$(BIN_DIR) $(OBJ_DIR):
	@mkdir -pv $@

clean:
	@$(RM) -rvf $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
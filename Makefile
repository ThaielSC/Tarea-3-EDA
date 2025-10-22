# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
LDFLAGS =

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Find all .cpp files recursively under src
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

# Generate object file names from source files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/EdaCal

.PHONY: all run clean

# Default rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	@echo "Linking..."
	@$(CXX) $(LDFLAGS) -o $@ $^

# Compilation rule for .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the program
run: all
	@echo "Running program..."
	@./$(TARGET)

# Rule to clean the project
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)


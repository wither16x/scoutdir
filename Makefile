BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
SRC_DIR := src
INCLUDE_DIR := include

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.cpp.o,$(SOURCES))
TARGET := $(BIN_DIR)/scoutdir

CXX := clang++
LD := clang++

CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wundef -Wunused \
		-Wcast-qual -Wconversion -Wsign-conversion -Wformat=2 -I$(INCLUDE_DIR)
LDFLAGS := -fuse-ld=lld -lcurl

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@echo "LD $^ -> $@"
	@$(LD) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "CXX $< -> $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
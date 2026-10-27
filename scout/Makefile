MAKEFLAGS += --no-print-directory

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

CXX := clang++
LD := clang++

CXXFLAGS := -std=c++23 -Wall -Wextra -Wshadow -Wpedantic -Wundef \
	-Wnon-virtual-dtor -Wold-style-cast -Wcast-qual -Wconversion -Wsign-conversion \
	-I$(INC_DIR)
LDFLAGS := -fuse-ld=lld

CXXFILES := $(shell find $(SRC_DIR) -name '*.cpp')
CXXOBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.cpp.o,$(CXXFILES))

TARGET := $(BIN_DIR)/scout

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(CXXOBJS)
	@mkdir -p $(dir $@)
	@echo "LD $< -> $@"
	@$(LD) $(LDFLAGS) $< -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "CXX $< -> $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
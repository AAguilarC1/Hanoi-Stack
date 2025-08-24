NAME := Hanoi_Tower

SRC_DIR := src
LIB_DIR := lib
INC_DIR := ./include/
BUILD_DIR := build
BIN_DIR := bin
TESTS_DIR := ./tests
TESTS_INC_DIR := $(TESTS_DIR)/include/
DATA_DIR := data

DIRS += $(BUILD_DIR) $(BIN_DIR)

dbg ?= 0
asan ?= 0

num_disks ?= 3

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRC:src/%.c=build/%.o)

TEST_SRC := $(wildcard $(TESTS_DIR)/*.c)
INCS := $(wildcard $(INC_DIR)/*.h)

CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__ -fPIC

LDFLAGS := -lm 

TARGET := $(BIN_DIR)/$(NAME)
TEST_TARGET := $(BIN_DIR)/$(NAME)_test

ifeq ($(asan), 1)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -static-libsan -g 
endif

ifeq ($(dbg), 1)
    CFLAGS += -g -O0 
else
    CFLAGS += -O3
endif

$(OBJS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ $(LDFLAGS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
$(TEST_TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I$(TESTS_INC_DIR) -I$(INC_DIR) $(filter-out build/main.o, $(OBJS)) $(TEST_SRC) -o $@ -lcunit $(LDFLAGS)

all : build $(TARGET)

MAKE_DIRS :
	@mkdir -p $(DIRS)

build : MAKE_DIRS $(OBJS)

check : all
	 valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(TARGET)

cache : all 
	 valgrind --cachegrind-out-file=$(DATA_DIR)/cachegrind.out --tool=cachegrind $(TARGET)
	 cg_annotate $(DATA_DIR)/cachegrind.out > $(DATA_DIR)/cachegrind.annotate

test : build $(TEST_TARGET)
	$(TEST_TARGET)

setup:
	 @sudo apt install -y valgrind
	 @sudo apt install -y lcunit1 libcunit1-dev libcuint1-doc
	 @sudo apt install -y clang
	 @sudo apt install -y bear

run : all
	$(TARGET) $(num_disks)

debug: all
	 gdb $(TARGET)

clean :
	$(RM) $(OBJS)
	$(RM) $(BIN_DIR)/*
	$(RM) $(DATA_DIR)/cachegrind*

.PHONY: all clean run check test setup


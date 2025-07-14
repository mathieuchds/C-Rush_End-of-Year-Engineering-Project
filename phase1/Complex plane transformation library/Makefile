CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lm -lSDL2 -lSDL2_image -lSDL2_ttf

SRC_DIR=src
BUILD_DIR=build
EXEC=$(BUILD_DIR)/main

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

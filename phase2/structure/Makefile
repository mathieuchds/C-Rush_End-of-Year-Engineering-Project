CC = gcc
CFLAGS = -Wall -I./src
SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))
LIB = $(BUILD_DIR)/libstructure.a

all: $(BUILD_DIR) $(LIB)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	ar rcs $@ $^
clean:
	rm -rf $(BUILD_DIR)/*.o $(LIB)
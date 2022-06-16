CC = gcc
CFLAGS = -Wall -Wextra -g -lpthread
BUILD_DIR = build
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
EXEC = parking-management

.PHONY: all clean

all : dir $(BUILD_DIR)/$(EXEC)

dir : 
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXEC) : $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_FILES) : $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(EXEC)


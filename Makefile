
CC = gcc
AR = ar

CPPFLAGS = -Iinclude
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
DEPFLAGS = -MMD -MP

BUILD_DIR = build
SRC_DIR = src
EXAMPLE_DIR = examples

SOURCES = $(wildcard $(SRC_DIR)/*.c)
EXAMPLES = $(wildcard $(EXAMPLE_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS = $(OBJECTS:.o=.d)

EXAMPLE_BINS = $(patsubst $(EXAMPLE_DIR)/%.c,$(BUILD_DIR)/%,$(EXAMPLES))

LIBRARY = $(BUILD_DIR)/libdatastructures.a

.PHONY: all library examples run clean

all: library examples

library: $(LIBRARY)

examples: $(EXAMPLE_BINS)

$(LIBRARY): $(OBJECTS) | $(BUILD_DIR)
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR)/%: $(EXAMPLE_DIR)/%.c $(LIBRARY) | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LIBRARY) -o $@

run: all
	@test -n "$(EXAMPLE)" || (echo "Usage: make run EXAMPLE=vector_example"; exit 1)
	./$(BUILD_DIR)/$(EXAMPLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)


CC  = gcc
AR  = ar
MODE = release

SRC_DIR     = src
INC_DIR     = include
EXAMPLE_DIR = examples
OUT         = build/$(MODE)

WARNINGS = -std=c11 -Wall -Wextra -Wpedantic

ifeq ($(MODE),release)
  MODE_FLAGS = -O2
else ifeq ($(MODE),debug)
  MODE_FLAGS = -O0 -g3 -fno-omit-frame-pointer \
               -fsanitize=address,undefined -fno-sanitize-recover=undefined
else ifeq ($(MODE),valgrind)
  MODE_FLAGS = -O0 -g3
else
  $(error Unknown MODE '$(MODE)' - use release, debug or valgrind)
endif

CFLAGS = $(WARNINGS) $(MODE_FLAGS) -I$(INC_DIR) -MMD -MP

SOURCES  = $(wildcard $(SRC_DIR)/*.c)
EXAMPLES = $(wildcard $(EXAMPLE_DIR)/*.c)

OBJECTS       = $(SOURCES:$(SRC_DIR)/%.c=$(OUT)/%.o)
EXAMPLE_NAMES = $(notdir $(EXAMPLES:.c=))
EXAMPLE_BINS  = $(addprefix $(OUT)/,$(EXAMPLE_NAMES))
LIBRARY       = $(OUT)/libdatastructures.a

EXAMPLE ?= $(firstword $(EXAMPLE_NAMES))

SAN_ENV = ASAN_OPTIONS=detect_leaks=1:strict_string_checks=1:detect_stack_use_after_return=1 \
          UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
                    --error-exitcode=1

.PHONY: all release debug examples run check valgrind clean

all: $(LIBRARY) $(EXAMPLE_BINS)

release:
	@$(MAKE) --no-print-directory MODE=release all

debug:
	@$(MAKE) --no-print-directory MODE=debug all

examples: $(EXAMPLE_BINS)

$(LIBRARY): $(OBJECTS)
	$(AR) rcs $@ $^

$(OUT)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/%: $(EXAMPLE_DIR)/%.c $(LIBRARY)
	$(CC) $(CFLAGS) $< $(LIBRARY) -o $@

run: all
	@test -n "$(EXAMPLE)" || { echo "No examples found in $(EXAMPLE_DIR)/"; exit 1; }
	$(if $(filter debug,$(MODE)),$(SAN_ENV) )./$(OUT)/$(EXAMPLE)

check:
	@$(MAKE) --no-print-directory MODE=debug all
	@for e in $(EXAMPLE_NAMES); do \
	    echo "==> $$e (ASan + UBSan + LSan)"; \
	    $(SAN_ENV) ./build/debug/$$e || exit 1; \
	done

valgrind:
	@$(MAKE) --no-print-directory MODE=valgrind all
	@for e in $(EXAMPLE_NAMES); do \
	    echo "==> $$e (Valgrind)"; \
	    $(VALGRIND) ./build/valgrind/$$e || exit 1; \
	done

clean:
	rm -rf build

-include $(OBJECTS:.o=.d) $(EXAMPLE_BINS:=.d)

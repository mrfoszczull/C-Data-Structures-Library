CC   = gcc
AR   = ar
MODE = release

SRC_DIR     = src
INC_DIR     = include
EXAMPLE_DIR = examples
TEST_DIR    = tests
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
TESTS    = $(wildcard $(TEST_DIR)/test_*.c)

OBJECTS       = $(SOURCES:$(SRC_DIR)/%.c=$(OUT)/%.o)
EXAMPLE_NAMES = $(notdir $(EXAMPLES:.c=))
TEST_NAMES    = $(notdir $(TESTS:.c=))

EXAMPLE_BINS = $(addprefix $(OUT)/,$(EXAMPLE_NAMES))
TEST_BINS    = $(addprefix $(OUT)/tests/,$(TEST_NAMES))

LIBRARY = $(OUT)/libdatastructures.a

EXAMPLE ?= $(firstword $(EXAMPLE_NAMES))

SAN_ENV = ASAN_OPTIONS=detect_leaks=1:strict_string_checks=1:detect_stack_use_after_return=1 \
          UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all \
                    --track-origins=yes --error-exitcode=1

.PHONY: all release debug examples run \
        check check-run \
        test test-run test-list test-list-run \
        test-vector test-vector-run \
        valgrind valgrind-run clean

all: $(LIBRARY) $(EXAMPLE_BINS)

release:
	@$(MAKE) --no-print-directory MODE=release all

debug:
	@$(MAKE) --no-print-directory MODE=debug all

examples: $(EXAMPLE_BINS)

$(LIBRARY): $(OBJECTS)
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

$(OUT)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/%: $(EXAMPLE_DIR)/%.c $(LIBRARY)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< $(LIBRARY) -o $@

$(OUT)/tests/test_%: $(TEST_DIR)/test_%.c $(LIBRARY)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< $(LIBRARY) -o $@

run: all
	@test -n "$(EXAMPLE)" || { \
	    echo "No examples found in $(EXAMPLE_DIR)/"; exit 1; \
	}
	@test -x "$(OUT)/$(EXAMPLE)" || { \
	    echo "Example '$(EXAMPLE)' not found in $(OUT)/"; exit 1; \
	}
	$(if $(filter debug,$(MODE)),$(SAN_ENV) )./$(OUT)/$(EXAMPLE)

test:
	@$(MAKE) --no-print-directory MODE=debug test-run

test-run: $(TEST_BINS)
	@test -n "$(TEST_BINS)" || { \
	    echo "No tests found in $(TEST_DIR)/"; exit 1; \
	}
	@set -e; for t in $(TEST_BINS); do \
	    echo "==> $$t (ASan + UBSan + LSan)"; \
	    $(SAN_ENV) ./$$t; \
	done

test-list:
	@$(MAKE) --no-print-directory MODE=debug test-list-run

test-list-run: $(OUT)/tests/test_list
	$(SAN_ENV) ./$(OUT)/tests/test_list

test-vector:
	@$(MAKE) --no-print-directory MODE=debug test-vector-run

test-vector-run: $(OUT)/tests/test_vector
	$(SAN_ENV) ./$(OUT)/tests/test_vector

check:
	@$(MAKE) --no-print-directory MODE=debug check-run

check-run: all $(TEST_BINS)
	@set -e; for e in $(EXAMPLE_NAMES); do \
	    echo "==> $$e (ASan + UBSan + LSan)"; \
	    $(SAN_ENV) ./$(OUT)/$$e; \
	done
	@test -n "$(TEST_BINS)" || { \
	    echo "No tests found in $(TEST_DIR)/"; exit 1; \
	}
	@set -e; for t in $(TEST_BINS); do \
	    echo "==> $$t (ASan + UBSan + LSan)"; \
	    $(SAN_ENV) ./$$t; \
	done

valgrind:
	@$(MAKE) --no-print-directory MODE=valgrind valgrind-run

valgrind-run: all $(TEST_BINS)
	@set -e; for e in $(EXAMPLE_NAMES); do \
	    echo "==> $$e (Valgrind)"; \
	    $(VALGRIND) ./$(OUT)/$$e; \
	done
	@test -n "$(TEST_BINS)" || { \
	    echo "No tests found in $(TEST_DIR)/"; exit 1; \
	}
	@set -e; for t in $(TEST_BINS); do \
	    echo "==> $$t (Valgrind)"; \
	    $(VALGRIND) ./$$t; \
	done

clean:
	rm -rf build

-include $(OBJECTS:.o=.d) \
         $(EXAMPLE_BINS:=.d) \
         $(TEST_BINS:=.d)


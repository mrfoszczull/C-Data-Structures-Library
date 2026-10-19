# C Data Structures Library

A collection of data structures implemented in C for learning purposes and practical experimentation. The project focuses on data structure implementation, dynamic memory management, API design, and testing.

## Features

- **Dynamic array (`Vector`)** of integers
- **Singly linked list (`List`)** of integers
- **Generic stack (`Stack`)** that stores copies of fixed-size elements
- Dynamic memory allocation and deallocation
- Bounds checking and error handling
- Insertion, removal, and element modification
- Configurable builds using GNU Make
- Example programs for each data structure
- Unit tests using assertions
- Memory and undefined behavior checks using AddressSanitizer, UndefinedBehaviorSanitizer, LeakSanitizer, and Valgrind

## Data Structures

### Vector

A dynamically allocated array of integers.

Supported operations:

- Initialize and destroy
- Append and remove the last element
- Get and set elements by index
- Reserve additional capacity
- Resize the array, initializing new elements to zero
- Clear all elements while retaining allocated capacity
- Query size and capacity

### List

A singly linked list of integers.

Supported operations:

- Initialize and destroy
- Insert and remove elements at the front or back
- Get and set elements by index
- Insert and remove elements at an arbitrary index
- Query the number of elements and check whether the list is empty
- Clear all elements while keeping the list initialized

### Stack

A generic, dynamically allocated LIFO (Last In, First Out) stack. It stores copies of elements of a fixed size specified during initialization.

Supported operations:

- Initialize and destroy
- Push an element onto the top of the stack
- Pop and retrieve the top element
- Peek at the top element without removing it
- Query the number of elements
- Check whether the stack is empty
- Clear all elements while retaining allocated capacity
- Automatically increase capacity when needed

The stack stores elements as raw bytes. Structures containing pointers are copied shallowly; the memory referenced by those pointers is not duplicated.

## Project Structure

```text
.
├── include/
│   ├── list.h
│   ├── stack.h
│   └── vector.h
├── src/
│   ├── list.c
│   ├── stack.c
│   └── vector.c
├── examples/
│   ├── list_example.c
│   ├── stack_example.c
│   └── vector_example.c
├── tests/
│   ├── test_list.c
│   ├── test_stack.c
│   └── test_vector.c
├── build/              # Generated build artifacts
├── Makefile
├── .gitignore
├── LICENSE
└── README.md
```

The `build/` directory contains separate outputs for each build mode: `release`, `debug`, and `valgrind`.

## Requirements

- A C11-compatible compiler, such as GCC or Clang
- GNU Make
- Valgrind (optional, required for `make valgrind`)

## Build

Build the static library and all example programs in release mode (`-O2`):

```bash
make
```

Build the library and examples with debugging symbols,
AddressSanitizer, and UndefinedBehaviorSanitizer enabled:

```bash
make debug
```

The compiler and archiver can be overridden from the command line:

```bash
make CC=clang
make CC=gcc
```

By default, the build uses the system C compiler available as `cc` and the system archiver available as `ar`.

The available build modes are:

| Mode | Compiler flags | Purpose |
|---|---|---|
| `release` | `-O2` | Optimized build |
| `debug` | `-O0 -g3` and sanitizers | Debugging and testing |
| `valgrind` | `-O0 -g3` | Memory analysis with Valgrind |

Each mode uses a separate output directory, so object files from different modes are not mixed.

## Run Examples

Run the default example:

```bash
make run
```

Run a specific example:

```bash
make run EXAMPLE=vector_example
make run EXAMPLE=list_example
make run EXAMPLE=stack_example
```

Run an example with sanitizers enabled:

```bash
make run MODE=debug EXAMPLE=vector_example
make run MODE=debug EXAMPLE=list_example
make run MODE=debug EXAMPLE=stack_example
```

## Tests

Run all unit tests with AddressSanitizer, UndefinedBehaviorSanitizer,
and LeakSanitizer:

```bash
make test
```

Run tests for a specific data structure:

```bash
make test-list
make test-vector
make test-stack
```

All test targets use the debug build with AddressSanitizer,
UndefinedBehaviorSanitizer, and LeakSanitizer enabled.

## Memory Debugging

Run all examples and unit tests under Valgrind:

```bash
make valgrind
```

Valgrind checks for memory leaks, invalid memory accesses,
and other memory-management errors.

Run all examples and unit tests with sanitizers:

```bash
make check
```

Sanitizers and Valgrind are run separately. Sanitizers help detect errors such as out-of-bounds access, use-after-free, and undefined behavior. Valgrind provides an additional check for memory errors and leaks.

A successful run means no issues were detected in the executed code paths; it does not prove that every possible input is handled correctly.

## Clean

Remove all generated build artifacts:

```bash
make clean
```

## Make Targets

| Target | Description |
|---|---|
| `make` | Build the library and examples in release mode |
| `make release` | Build explicitly in release mode |
| `make debug` | Build the library and examples with sanitizers |
| `make run` | Build and run an example |
| `make test` | Run all tests with sanitizers |
| `make test-list` | Run list tests with sanitizers |
| `make test-vector` | Run vector tests with sanitizers |
| `make test-stack` | Run stack tests with sanitizers |
| `make check` | Run all examples and tests with sanitizers |
| `make valgrind` | Run all examples and tests under Valgrind |
| `make clean` | Remove the `build/` directory |

## Implementation Status

| Data Structure | Status |
|---|---|
| Dynamic Array (`Vector`) | Implemented |
| Singly Linked List (`List`) | Implemented |
| Generic Stack (`Stack`) | Implemented |

## Learning Goals

This project explores:

- Data structures and algorithmic complexity
- Pointers and pointer manipulation
- Dynamic memory allocation (`malloc`, `realloc`, `free`)
- Memory ownership and resource cleanup
- Generic programming in C using `void *`
- API design and header files
- Modular C programming
- Unit testing and defensive programming
- Debugging memory errors with sanitizers and Valgrind

## License

This project is licensed under the [MIT License](LICENSE).

Copyright (c) 2026 mrfoszczull

You are free to use, copy, modify, merge, publish, distribute, sublicense, and sell copies of the software, subject to the terms of the MIT License.

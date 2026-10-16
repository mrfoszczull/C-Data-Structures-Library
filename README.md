# C Data Structures Library

A collection of data structures implemented in C for learning purposes and practical experimentation.

## Features

- Dynamic array (`Vector`) of integers
- Dynamic memory management
- Bounds checking for element access
- Configurable build using GNU Make (release, sanitizer and Valgrind modes)
- Example program demonstrating the library

## Project Structure

```
.
├── include/       # Public header files
├── src/           # Library implementations
├── examples/      # Example programs
├── build/         # Generated build artifacts (one subdirectory per build mode)
├── Makefile
├── .gitignore
└── README.md
```

## Requirements

- GCC or another compatible C compiler
- GNU Make
- Optional: Valgrind (for `make valgrind`)

## Build

Build the library and all examples in release mode (`-O2`):

```
make
```

Build with AddressSanitizer, UndefinedBehaviorSanitizer and LeakSanitizer
(`-O0 -g3`):

```
make debug
```

Each mode is built into its own directory (`build/release`, `build/debug`,
`build/valgrind`), so switching between modes never mixes incompatible object files.

## Run

Build and run an example (the first one found if `EXAMPLE` is not given):

```
make run
make run EXAMPLE=vector_example
```

Run an example with sanitizers enabled:

```
make run MODE=debug EXAMPLE=vector_example
```

## Debugging Memory Errors and Undefined Behavior

Build in debug mode and run every example under ASan, UBSan and LSan. The
command stops with a non-zero exit code and a stack trace on the first problem
(out-of-bounds access, use-after-free, memory leak, signed overflow, ...):

```
make check
```

Run every example under Valgrind (`-O0 -g3` build, full leak check):

```
make valgrind
```

Sanitizers and Valgrind cannot be combined, which is why they are separate
modes. LeakSanitizer is supported on Linux; on macOS use Valgrind or `leaks`
instead.

## Clean

Remove all generated build artifacts:

```
make clean
```

## Make Targets

| Target                | Description                                            |
| --------------------- | ------------------------------------------------------ |
| `make`                | Release build of the library and examples              |
| `make debug`          | Build with ASan + UBSan + LSan                         |
| `make run`            | Build and run an example (`EXAMPLE=name`, `MODE=debug`) |
| `make check`          | Run all examples under sanitizers                      |
| `make valgrind`       | Run all examples under Valgrind                        |
| `make clean`          | Remove `build/`                                        |

## Current Data Structures

| Data Structure           | Status      |
| ------------------------ | ----------- |
| Dynamic Array (`Vector`) | Implemented |

## Learning Goals

This project is intended to explore data structures, memory management, pointers, dynamic allocation, and modular programming in C.

## License

No license has been specified yet.

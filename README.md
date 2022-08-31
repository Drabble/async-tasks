# Async Tasks

## What is Async Tasks?

Async Tasks is a c++ library to create and handle finite asynchronous 
processes and handle their lifecycle using commands such
as pause, resume, stop.

## Project Structure

The project is structured as follows:

- **cli**: contains the cli application used to interact with the library
- **tests**: contains tests for the library
- **lib**: contains the async-tasks library

## How to run cli

```bash
# Generate the project buildsystem
cmake -S . -B build

# Build the project
cmake --build build

# Run the cli
./build/cli/cli
```

## How to run tests

```bash
# Generate the project buildsystem
cmake -S . -B build

# Build the project
cmake --build build

# Run the tests
./build/tests/test
```
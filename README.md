# Async Tasks

## What is Async Tasks?

Async Tasks is a c++ library to create finite asynchronous
processes and handle their lifecycle using commands such as pause, resume, stop.

## Project Structure

The project is structured as follows:

- **cli**: contains the cli application used to interact with the library
- **lib**: contains the async-tasks library
- **tests**: contains tests for the library

## How to run cli

```bash
# Generate the project buildsystem
cmake -S . -B build

# Compile the project
cmake --build build

# Run the cli
./build/cli/cli
```

## How to run tests

```bash
# Generate the project buildsystem
cmake -S . -B build

# Compile the project
cmake --build build

# Run the tests
./build/tests/test
```

## Future improvements

- We can potentially improve thread creation with a thread pool. This would allow reuse of
old threads, instead of recreating them. Creating a thread has a big overhead.

- Benchmarking task execution for multiple use cases. Asynchronous vs synchronous, 
long iterations vs small iterations, thread pool vs no thread pool, using atomics instead of a condition variable.

- Passing arguments to the async tasks directly through the CLI. For example the name of
a file to read.

- Setting up a CI for automated testing with a tool such as GitHub Actions. 

- Caching async tasks when the number of tasks under execution is above a certain threshold. There is a limit
to the number of concurrent threads that varies on different systems.

- Tests should be improved to avoid using thread sleep. Thread sleep does not always execute in the same way depending
on the underlying machine and CPU load.

## Style guide

This project tries to follow [Bjarne Stroustrup's C++ Style and Technique FAQ](https://www.stroustrup.com/bs_faq2.html).
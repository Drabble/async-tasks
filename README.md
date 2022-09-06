# Async Tasks

## What is Async Tasks?

Async Tasks is a c++ library to create and handle finite asynchronous
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

We can potentially improve thread creation with a thread pool. This would allow reuse of
old threads, instead of recreating them. Creating a thread has a big overhead.

It would be interesting to try to use atomics instead of mutexes in the thread to
avoid blocking calls.

Benchmarking the tasks to compare multiple elements. Asynchronous vs synchronous, 
long iterations vs small iterations in a task, thread pool vs no thread pool for handling
a lot of tasks.

## Style guide

This project tries to follow [Bjarne Stroustrup's C++ Style and Technique FAQ](https://www.stroustrup.com/bs_faq2.html).
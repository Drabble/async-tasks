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

Benchmarking the tasks to compare multiple elements. Asynchronous vs synchronous, 
long iterations vs small iterations in a task, thread pool vs no thread pool for handling
a lot of tasks.

Reading arguments that follow the *start* command would allow us to pass these arguments to
the related task factory and instantiate a task with custom arguments. For example the name of
a file to read.

Setting up a CI for automated testing with a tool such as GitHub Actions. 

Caching async tasks when the number of tasks under execution is above a certain threshold. There is a limit
to the number of concurrent thread depending on the system.

Tests should be improved to avoid using thread sleep. Thread sleep does not always execute in the same way based
on the underlying machine and the CPU load.

## Style guide

This project tries to follow [Bjarne Stroustrup's C++ Style and Technique FAQ](https://www.stroustrup.com/bs_faq2.html).
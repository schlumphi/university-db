# Mini University Database Project

This is a **mini project** demonstrating a simple student database with unit tests using **Google Test**.

## Features

The database allows you to:

- Add new students
- Search students by **PESEL** or **last name**
- Delete students by **index number**
- Display the database
- Save the database to a file and load it back

## Build Instructions

1. Create a build directory in the main project folder:

```bash
mkdir build
cd build
```

2. Generate the build system using CMake:

```bash
cmake ..
```

3. Compile the project:

```bash
make -j
```

## Running Unit Tests

Run all unit tests using CTest:

```bash
ctest
```

This will execute all the tests defined for the database, including add, delete, search, sort, save/load operations and
few tests for helper classes.

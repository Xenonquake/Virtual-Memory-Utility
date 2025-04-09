# VirtMaxU Program

## Overview
VirtMaxU is a simple C23 program designed to list and analyze the virtual memory usage of processes running on a Linux system. This program reads process information from the `/proc` directory, sorts the processes by their virtual memory usage, and displays the top ten processes with the highest memory consumption.

## Purpose
The VirtMaxU program is developed for educational purposes. It aims to provide a practical example of how to use the C programming language to interact with the Linux operating system, read and parse system files, and manage memory effectively.

## Features
- Reads process information from the `/proc` directory.
- Parses the process name and virtual memory size from the `/proc/[pid]/status` files.
- Sorts processes by virtual memory usage in descending order.
- Displays the top ten processes with the highest memory usage.
- Supports a `--debug` flag for verbose output.

## Requirements
- A Linux-based operating system.
- GCC or Clang compiler with C23 support.

## Compilation
To compile the VirtMaxU program, use the following command:

```bash
    gcc -std=c23 -o VirtMaxU main.c
```

or

```bash
    clang -std=c23 -o VirtMaxU main.c
```

## Usage
Run the compiled program with the following command:

```bash
    ./VirtMaxU
```

The program will output the top ten processes with the highest virtual memory usage.

To enable debug mode, use the `--debug` flag:

```bash
    ./VirtMaxU --debug
```

## Code Explanation
The main components of the VirtMaxU program include:

1. **Process Information Structure**: A structure to store the process ID, name, and virtual memory size.
2. **Comparison Function**: A function to compare processes by their virtual memory size for sorting.
3. **Process Information Retrieval**: A function to read and parse process information from the `/proc/[pid]/status` files.
4. **Memory Management**: Dynamic memory allocation and resizing for storing process information.
5. **Sorting and Display**: Sorting the processes by virtual memory usage and displaying the top ten processes.

## Learning Objectives
The development of the VirtMaxU program aims to enhance understanding of the following concepts:
- **C Programming Language**: Building a practical application using modern C23 features.
- **Memory Management**: Dynamic memory allocation, resizing, and deallocation.
- **File I/O**: Reading and parsing system files in the `/proc` directory.
- **System Programming**: Interacting with the Linux operating system and retrieving process information.
- **Data Structures and Algorithms**: Using arrays, structures, and sorting algorithms to manage and analyze data.

## Contribution
Contributions to the VirtMaxU program are welcome. If you have any suggestions, improvements, or new features to add, please feel free to submit a pull request or open an issue.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact
If you have any questions or would like to learn more about C programming and memory management, please feel free to reach out.
[xenonquake@gmail.com]

Happy coding!

## Haskell Environment Setup and Shake Build Instructions

### Setting Up Haskell Environment

1. **Verify/Install Haskell Environment**:
   - Ensure you have a suitable Haskell compiler (GHC >= version X.Y) and a build tool (Stack or Cabal).
   - For Void Linux, you can install them using:
     ```bash
     xbps-install -S ghc cabal-install stack
     ```

2. **Integrate Shake Dependency**:
   - Initialize a Haskell project if one doesn't exist:
     ```bash
     stack new <project> simple
     ```
     or
     ```bash
     cabal init
     ```
   - Add the `shake` library package as a dependency in the appropriate configuration file (build-depends section).
   - Execute dependency resolution:
     ```bash
     stack build --dependencies-only
     ```
     or
     ```bash
     cabal build --dependencies-only
     ```

3. **Define Build Artifact Directory Structure**:
   - Designate a subdirectory for build outputs (e.g., `_build/`).
   - Create this directory structure notionally or physically.

### Running the Shake Build

1. **Default Build**:
   - To build the main executable, run:
     ```bash
     stack exec -- runhaskell Shakefile.hs
     ```
     or
     ```bash
     runhaskell Shakefile.hs
     ```

2. **Clean Build Directory**:
   - To clean the build directory, run:
     ```bash
     stack exec -- runhaskell Shakefile.hs clean
     ```
     or
     ```bash
     runhaskell Shakefile.hs clean
     ```

3. **Build Test Executable**:
   - To build the test executable, run:
     ```bash
     stack exec -- runhaskell Shakefile.hs test
     ```
     or
     ```bash
     runhaskell Shakefile.hs test
     ```

### Available Targets

- **Default**: Builds the main executable.
- **Clean**: Cleans the build directory.
- **Test**: Builds the test executable.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact
If you have any questions or would like to learn more about C programming and memory management, please feel free to reach out.
[xenonquake@gmail.com]

Happy coding!

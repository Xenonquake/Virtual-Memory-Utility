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
=======
Virtual memory utility

A lightweight C program to monitor memory usage of running processes on a Unix-like system. This tool scans the /proc filesystem, collects process information (PID, name, and virtual memory size), sorts processes by memory usage, and displays the top 10 memory-intensive processes. Written as an educational exercise to explore C programming, memory management, and POSIX system interfaces.
Overview

  Purpose: Educational tool to learn C programming, system-level process inspection, and memory handling.
  Functionality:
        Reads process data from /proc/[pid]/status.
        Extracts PID, process name, and virtual memory size (VmSize).
        Sorts processes in descending order by memory usage.
        Prints the top 10 processes with the highest virtual memory usage.
    Features:
        Dynamic memory allocation with malloc and realloc.
        POSIX-compliant for portability across Unix-like systems.
        Uses C23 attributes (e.g., [[nodiscard]]) for modern C practices.

License
This project is licensed under the MIT License. See the LICENSE (#license) section below for details.
Prerequisites

  Operating System: Unix-like with /proc filesystem (e.g., Linux). Tested on Void Linux.
  Compiler: Clang with C23 support (-std=c23).
  Libraries: Standard C and POSIX libraries (no external dependencies beyond libc).

Install Clang on Void Linux if needed:

    xbps-install -S clang

Setup

  Clone or Copy the Code:
    Save the code as memory_checker.c in a directory (e.g., memory-checker).
  
  Compile the Program:

    clang -std=c23 -o VirtMaxMem main.c

Usage
Running the Program

Execute the compiled binary:

    ./VirtMaxMem

Output Example:
```
PID    NAME              VMSIZE (kB)
1234   firefox          1234567
5678   chrome           987654
91011  plasma-desktop   456789
1213   Xorg             234567
1415   gnome-shell      198765
1617   dockerd          167890
1819   code             145678
2021   slack            123456
2223   mysqld           111222
2425   zoom             98765
```
Lists the top 10 processes by virtual memory size (VmSize) in kilobytes.

Notes

  Requires read access to /proc (typically available to all users on Linux).
  If fewer than 10 processes are running, it displays all available processes.

Project Notes

  Educational Goals:
        
  C Programming: Explores structs, dynamic memory (malloc, realloc), and sorting with qsort.
  C23: Uses modern C23 features like [[nodiscard]] for better code quality.
  OSIX: Leverages /proc filesystem and POSIX functions (opendir, readdir) for system interaction.
  
  Development: Written to understand process memory usage and system programming concepts in a POSIX environment.
  
  Limitations: 
        Single-threaded and non-configurable (fixed top 10 output).
        No filtering options (e.g., by process name or memory threshold).

Debugging Tips

  Permission Issues: If /proc/[pid]/status files are inaccessible, run with elevated privileges (sudo/doas ./memcheck), though this is rare for user-owned processes.
    Memory Errors: Check for allocation failures in output (e.g., "Failed to allocate memory").
    Verbose Output: Add printf statements in get_process_info to debug parsing issues.

License
This project is licensed under the MIT License.

MIT License

Copyright (c) 2025 River

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Acknowledgments

   
Inspired by curiosity about process memory usage on Linux systems.
Tested on Void Linux, leveraging its lightweight environment.


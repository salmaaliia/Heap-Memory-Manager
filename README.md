# Heap Memory Manager

## Overview
This project implements a custom heap memory manager in C. It provides dynamic memory allocation and deallocation services in the real heap. The project includes functions like `Hmmalloc`, `Hmmfree`, and `Hmmsbrk` to manage memory within the heap.

## Features
- **Custom Memory Allocation (`Hmmalloc`)**: Allocates memory blocks in the real heap using a best-fit strategy.
- **Memory Deallocation (`Hmmfree`)**: Frees allocated memory and combines contiguous free blocks.
- **Custom Memory Reallocation (`Hmmrealloc`)**
- **Custom Zero-initialized Memory Allocation (`Hmmcalloc`)**
- **Linked List Management for Free Blocks**
- **Simulated Program Break Management (`Hmmsbrk`)**: Adjusts the simulated program break to allocate or free heap space.

## Files
- `Hmmalloc.c` and `Hmmalloc.h`: Implements and declares the custom memory allocation function.
- `Hmmfree.c` and `Hmmfree.h`: Implements and declares the custom memory deallocation function.
- `Hmmcalloc.c` and `Hmmcalloc.h`: Implements the custom `calloc` function.
- `Hmmrealloc.c` and `Hmmrealloc.h`: Implements the custom `realloc` function.
- `Hmmsbrk.c` and `Hmmsbrk.h`: Wrapper for sbrk().
- `listHandling.c` and `listHandling.h`: Handles the linked list structure used for managing free memory blocks.
- `mydynamic.c` and `mydynamic.h`: Overrides the standard malloc, free, calloc, and realloc functions with custom implementations to enable custom memory management. 
- `Hmmalloc.pdf` and `Hmmfree.pdf`: Documentation for the respective functions.

## Compilation

### Step 1: Compile Source Files into Object Files

Compile all source files into position-independent code (PIC) object files using the following command:

```
gcc -g -c -fPIC -Wall Hmmalloc.c Hmmfree.c listHandling.c Hmmsbrk.c Hmmrealloc.c Hmmcalloc.c mydynamic.c
```
### Step 2: Create the Shared Library
Link the object files into a shared library named libmyheap.so:
```
gcc -shared -o libmyheap.so *.o
```
### Step 3: Link the Shared Library to Your Program
To compile a program (e.g., main.c) that uses this shared library, use the following command:
```
gcc -o main main.c -I ./mylib/ -L ./mylib/ -lmyheap
```
mylib is dircrory where the library exists.

### Step 4: Set the Library Path
Before running your program, ensure the dynamic linker can find your shared library by setting the LD_LIBRARY_PATH:
```
export LD_LIBRARY_PATH=./mylib
```
This command sets the LD_LIBRARY_PATH environment variable to the ./mylib directory and exports it so that it's available to all commands and programs executed in the current shell session.

### Step 5: Preload Your Library
To ensure your custom memory management functions are used instead of the default ones, you can preload your library:
```
LD_PRELOAD=./mylib/libmyheap.so ./main
```
You can use it to run bash commands also like `ls`, `bash`, `vim`
```
LD_PRELOAD=./mylib/libmyheap.so ls
LD_PRELOAD=./mylib/libmyheap.so bash
LD_PRELOAD=./mylib/libmyheap.so vim
```




<!--## Usage
-To use the heap memory manager in your projects, include the relevant header files and link the corresponding source files.
-You can make a shared library.

## Getting Started
1. Clone the repository:
   ```bash
   git clone https://github.com/salmaaliia/Heap-Memory-Manager.git
   ```
2. Include the necessary header files in your project.
   ```bash
   #include "Hmmalloc.h"
   #include "Hmmfree.h"
   ```
3. Compile the source files with your application.
   ```bash
   gcc -o app app.c listHandlinf.c Hmmalloc.c Hmmfree.c Hmmsbrk.c
   ```-->

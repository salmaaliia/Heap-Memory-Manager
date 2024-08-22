# Heap Memory Manager

## Overview
This project implements a custom heap memory manager in C. It provides dynamic memory allocation and deallocation services using a statically allocated array to simulate the heap area. The project includes functions like `Hmmalloc`, `Hmmfree`, and `Hmmsbrk` to manage memory within the simulated heap.

## Features
- **Custom Memory Allocation (`Hmmalloc`)**: Allocates memory blocks from the simulated heap using a best-fit strategy.
- **Memory Deallocation (`Hmmfree`)**: Frees allocated memory and combines contiguous free blocks.
- **Simulated Program Break Management (`Hmmsbrk`)**: Adjusts the simulated program break to allocate or free heap space.

## Files
- `Hmmalloc.c` and `Hmmalloc.h`: Implements and declares the custom memory allocation function.
- `Hmmfree.c` and `Hmmfree.h`: Implements and declares the custom memory deallocation function.
- `Hmmsbrk.c` and `Hmmsbrk.h`: Implements and declares the function to adjust the simulated program break.
- `listHandling.c` and `listHandling.h`: Handles the linked list structure used for managing free memory blocks.
- `Hmmalloc.pdf` and `Hmmfree.pdf`: Documentation for the respective functions.

## Usage
To use the heap memory manager in your projects, include the relevant header files and link the corresponding source files. Ensure that your memory requests align with the heap's size and available memory.

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
   ```

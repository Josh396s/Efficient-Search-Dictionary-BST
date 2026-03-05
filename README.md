# Dictionary ADT (Binary Search Tree Implementation)

A robust and efficient Dictionary Abstract Data Type (ADT) implemented in C++ using a **Binary Search Tree (BST)**. This project demonstrates high-performance data retrieval, the implementation of the iterator design pattern, and rigorous manual memory management.

## Technical Overview
The Dictionary is built on a non-linear linked structure (BST) that maintains keys in a sorted order. It is designed to provide efficient operations for managing key-value pairs:
- **Search & Insertion**: Average case time complexity of $O(\log n)$.
- **In-Order Traversal**: Provides keys in ascending order (alphabetical).
- **Pre-Order Traversal**: Useful for visualizing the tree structure or creating deep copies.
- **Iterator Pattern**: Includes a built-in iterator (`begin()`, `end()`, `next()`, `prev()`) for both forward and reverse traversal of the dataset.

## Features
- **Sentinel Node Design**: Utilizes a `nil` sentinel node to simplify edge cases in tree manipulations (like deletions and rotations).
- **Comprehensive ADT Operations**: Supports `setValue()`, `remove()`, `contains()`, and `getValue()`.
- **Memory Safety**: Implements a `postOrderDelete()` helper to ensure all dynamically allocated nodes are properly freed, resulting in zero memory leaks.
- **Client Interface**: Includes an `Order.cpp` utility that processes input files and outputs both in-order and pre-order representations of the data.

## Performance Profile
| Operation | Average Complexity | Worst Case |
|-----------|--------------------|------------|
| Search    | $O(\log n)$        | $O(n)$     |
| Insert    | $O(\log n)$        | $O(n)$     |
| Delete    | $O(\log n)$        | $O(n)$     |

## Build and Run

### Requirements
- G++ Compiler (C++17 standard)
- Make build system

### Installation
To compile the project and generate the `Order` executable:
```bash
make
```

### Usage
The Order client reads keys from an input file and saves the dictionary state to an output file:
```bash
./Order <input_file> <output_file>
```
To run the automated test suite:
```bash
make DictionaryTest
./DictionaryTest
```

### Cleaning
To remove all compiled binaries and object files:
```bash
make clean
```

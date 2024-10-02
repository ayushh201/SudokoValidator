# Sudoku Validator Using Multithreading

## Overview

This project is a simple Sudoku board validator written in C that uses multithreading to efficiently check whether a given 9x9 Sudoku grid is valid. It verifies rows, columns, and 3x3 subgrids in parallel using POSIX threads (pthreads).

## Features

- **Multithreaded Validation**: Uses multiple threads to validate rows, columns, and 3x3 subgrids concurrently.
- **Efficient Performance**: Parallel processing for faster validation.
- **Input Flexibility**: Supports board input from files or manual entry.

## How It Works

1. The Sudoku board is divided into rows, columns, and 3x3 subgrids.
2. A thread is created for each validation task (rows, columns, subgrids).
3. The program reports if the board is valid based on the Sudoku rules.

## Requirements

- GCC Compiler
- POSIX Threads (pthreads)

# Parallel Maximum Value Finder Using MPI

## Overview

This program demonstrates the use of MPI to parallelize the task of finding the maximum value in an array. The array is divided among multiple processes, and each process finds the maximum value in its assigned chunk. The results are then combined by the master process to determine the overall maximum value.

## Compilation

To compile the program, use the following command:
```bash
mpicc -o max_finder max_finder.c

# Autocomplete-Project
#Date Completed: Feb 26, 2023
#Author: Anthony Salgado and Harry Nguyen
# Autocomplete Project

## Overview

This project implements an autocomplete system that reads a list of terms with associated weights from a file and provides functionality to search for terms that start with a given prefix, sorting the matching terms by weight.

## Features

- **Lexicographical Sorting**: Sorts terms in lexicographic order.
- **Weight Sorting**: Sorts terms by weight in descending order.
- **Binary Search**: Uses binary search to efficiently find the range of terms matching a given prefix.
- **Autocomplete**: Returns terms starting with a specified prefix, sorted by their weights.

## Files

### `autocomplete.c`

The main C source file implementing key functions:

- `cmp_term`: Compares two terms lexicographically.
- `cmp_weights`: Compares the weights of two terms for descending order sorting.
- `read_in_terms`: Reads a list of terms and weights from a file, sorting the terms lexicographically.
- `lowest_match`: Performs a binary search to find the first term matching a given prefix.
- `highest_match`: Performs a binary search to find the last term matching a given prefix.
- `autocomplete`: Finds and returns all terms matching a given prefix, sorted by weight in descending order.

### `autocomplete.h`

Header file containing declarations for functions and structures used in `autocomplete.c`.

## Compilation and Execution

1. **Compiling**: Use the following command to compile the project:
   ```bash
   gcc autocomplete.c -o autocomplete -lm
2. After compiling, run the program with ./autocomplete
3. The input file (e.g., cities.txt) should be formatted as follows:
  n
weight    term
weight    term
...
Where:
n is the number of terms.
Each subsequent line contains a term and its corresponding weight, separated by a tab.
Example:
5
1000    New York
800     Los Angeles
600     Toronto
500     San Francisco
400     Chicago
The autocomplete function finds all terms matching the specified prefix and returns them sorted by weight. For instance, searching for the prefix "Tor" would yield Toronto with its corresponding weight.

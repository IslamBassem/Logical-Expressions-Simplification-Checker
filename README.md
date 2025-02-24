# Logical Expression Simplification Checker

## Overview

The **Logical Expression Simplification Checker** is a C++ program designed to verify the correctness of Boolean algebra simplifications. It takes two logical expressions—a complex expression and a simplified version—and evaluates their equivalence using truth tables.

## Features

- Generates a **truth table** for given logical expressions.
- Evaluates **Boolean expressions** with AND (`&`), OR (`|`), and NOT (`!`) operators.
- Compares the **truth table outputs** of the original and simplified expressions.
- Supports up to **23 variables** for expression evaluation.

## How It Works

1. The user inputs the **number of variables** and their names.
2. The program prompts for:
   - A **complex logical expression**.
   - A **simplified version** of the expression.
3. It generates **truth tables** for both expressions and checks if they are equivalent.
4. The program displays the **truth tables** and outputs whether the expressions are equivalent.

## Example Usage

### Input:

```
Enter the number of variables (1-23): 3
Enter the variable names (e.g., A B C): A B C
Enter the complex logical expression (AND: & / OR: | / NOT: !): ((A|B)&(A&B))|(B&!B)|(B&C)
Enter the simplified logical expression: (A&B)|(B&C)
```

### Output:

```
Truth Table for Complex Expression:
A B C | Result
0 0 0 | 0
0 0 1 | 0
0 1 0 | 0
0 1 1 | 0
1 0 0 | 0
1 0 1 | 0
1 1 0 | 1
1 1 1 | 1

Truth Table for Simplified Expression:
A B C | Result
0 0 0 | 0
0 0 1 | 0
0 1 0 | 0
0 1 1 | 0
1 0 0 | 0
1 0 1 | 0
1 1 0 | 1
1 1 1 | 1

The expressions are Equivalent.
```

## Code Structure

- **generateTruthTable(int num\_of\_variables):** Creates a truth table for the given number of variables.
- **applyOperation(char operation, bool left, bool right):** Evaluates AND (`&`) and OR (`|`) operations.
- **evaluate\_expression(const string& expression, const unordered\_map\<string, int>& values):** Evaluates a given logical expression using a stack-based approach.
- **compareExpressions():** Generates truth tables and checks if the two expressions produce identical results.

## Installation & Compilation

### Requirements:

- C++ compiler (e.g., `g++`)

### Compilation:

```sh
g++ -o logical_checker logical_checker.cpp
```

### Running the Program:

```sh
./logical_checker
```

## License

This project is licensed under the MIT License.

## Author

[Islam Bassem]


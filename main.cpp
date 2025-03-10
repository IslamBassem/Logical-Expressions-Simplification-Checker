#include <bits/stdc++.h>
using namespace std;

// truth table generation

vector<vector<int>> generateTruthTable(int num_of_variables) {
    int rows = pow(2, num_of_variables);
    vector<vector<int>> table(rows, vector<int>(num_of_variables, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < num_of_variables; j++) {
            table[i][j] = (i >> (num_of_variables - j - 1)) & 1;
        }
    }
    return table;
}

// Function to apply logical operators

bool applyOperation(char operation, bool left, bool right) {
    if (operation == '&') return left && right;
    if (operation == '|') return left || right;
    return false; // Invalid operation
}

// Function to evaluate the logical expression

bool evaluate_expression(const string& expression, const unordered_map<string, int>& values) {
    stack<bool> operands;
    stack<char> operators;

    auto operation_priority = [](char operation) {
        if (operation == '!') return 3;  // NOT has the highest priority
        if (operation == '&') return 2; // AND
        if (operation == '|') return 1; // OR
        return 0;
    };

    auto evaluateTop = [&]() {
        char operation = operators.top();
        operators.pop();
        if (operation == '!') {
            bool operand = operands.top();
            operands.pop();
            operands.push(!operand);
        } else {
            bool right = operands.top();
            operands.pop();
            bool left = operands.top();
            operands.pop();
            operands.push(applyOperation(operation, left, right));
        }
    };

    for (int i = 0; i < expression.size(); ++i) {
        char charachter = expression[i];
        if (isalpha(charachter)) { // Variable
            string var(1, charachter);
            operands.push(values.at(var));
        }

        else if (charachter == '(') { // parentheses
            operators.push(charachter);
        }

        else if (charachter == ')') {
            while (!operators.empty() && operators.top() != '(') {
                evaluateTop();
            }
            operators.pop(); // Remove '('
        }

        else if (charachter == '&' || charachter == '|' || charachter == '!') { // operator
            while (!operators.empty() && operation_priority(operators.top()) >= operation_priority(charachter)) {
                evaluateTop();
            }
            operators.push(charachter);
        }
    }

    while (!operators.empty()) {
        evaluateTop();
    }
    return operands.top();
}

// Function to compare expressions and print truth tables

bool compareExpressions(const vector<vector<int>>& truthTable, const string& complex_expression, const string& simplified_expression, const vector<string>& variables) {
    unordered_map<string, int> values;
    vector<bool> complex_results, simplified_results;

    cout << "\nTruth Table for Complex Expression:\n";
    for (const string& var : variables) cout << var << " ";
    cout << "| Result\n";

    for (const auto& row : truthTable) {
        for (int i = 0; i < variables.size(); i++) {
            values[variables[i]] = row[i];
        }
        bool result = evaluate_expression(complex_expression, values);
        complex_results.push_back(result);

        for (int val : row) cout << val << " ";
        cout << "| " << result << "\n";
    }
    cout << "\nTruth Table for Simplified Expression:\n";
    for (const string& var : variables) cout << var << " ";
    cout << "| Result\n";

    for (const auto& row : truthTable) {
        for (size_t i = 0; i < variables.size(); i++) {
            values[variables[i]] = row[i];
        }
        bool result = evaluate_expression(simplified_expression, values);
        simplified_results.push_back(result);
        for (int val : row) cout << val << " ";
        cout << "| " << result << "\n";
    }
    return complex_results == simplified_results;
}

// Main function
int main() {
    cout << setw(110) << "Logical Expression Equivalence Checker\n";
    int num_of_variables;
    cout << "Enter the number of variables (1-23): ";
    cin >> num_of_variables;

    vector<string> variables(num_of_variables);
    cout << "\nEnter the variable names (e.g., A B C): \n";
    for (int i = 0; i < num_of_variables; i++) {
        cin >> variables[i];
    }

    string complex_expression, simplified_expression;
    cout << "Enter the complex logical expression (AND: & / OR: | / NOT: !): ";

    // ((a|b)&(a&b))|(b&!b)|(b&c)

    cin.ignore();
    getline(cin, complex_expression);

    cout << "\n Enter the simplified logical expression: ";

    // (a&b)|(b&c)

    getline(cin, simplified_expression);

    // Generate truth table
    vector<vector<int>> truthTable = generateTruthTable(num_of_variables);

    // Compare expressions
    bool Equivalent = compareExpressions(truthTable, complex_expression, simplified_expression, variables);

    // Output result
    cout << "\nThe expressions are " << (Equivalent ? "Equivalent." : "Not Equivalent.") << "\n";

    return 0;
}
#include <iostream>  
#include <stack>  
#include <vector>  
#include <cmath>  
#include <string>  
#include <map>  
#include <memory>  
#include <stdexcept> 

using namespace std;

// Definition of the Node class representing a node in the expression tree 
class Node {
public:
    string value; // The value of the node, can be an operator or number 
    unique_ptr<Node> left; 
    unique_ptr<Node> right;

    // Constructor initializing node with a value and null children 
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Definition of the ExTree class 
class ExTree {
public:
    unique_ptr<Node> root; // Unique pointer to the root of the tree 

    // Constructor initializes the root to nullptr 
    ExTree() : root(nullptr) {}

    // Function to construct the tree from an input expression string 
    void constTree(const string& expression) {
        root = buildTree(expression); // Calls buildTree to parse and construct the tree
    }

    // Function to evaluate the expression tree and return its result 
    double evaluate() {
        return evaluateNode(root); // Calls evaluateNode starting from the root
    }

    // Function to display the tree in a visually appealing format 
    void display() {
        int depth = calculateDepth(root.get()); // Calculate the depth of the tree 
        int width = calculateWidth(depth); // Calculate the width for display based on depth

        vector<string> displayLines(depth, string(width, ' ')); // Create lines for display

        fillDisplay(displayLines, root.get(), 0, width / 2, depth); // Fill lines with node values

        // Print each line of the tree
        for (const auto& line : displayLines) {
            cout << line << endl;
        }
    }

private:
    // Helper function to evaluate nodes recursively 
    double evaluateNode(const unique_ptr<Node>& node) {
        if (!node->left && !node->right) { // If leaf node 
            try {
                return stod(node->value); // Try converting the value to double
            }
            catch (const invalid_argument& ia) { // Catch and handle invalid argument exception
                cerr << "Invalid numeric format: " << ia.what() << '\n';
                return 0;
            }
            catch (const out_of_range& orr) { // Catch and handle out of range exception
                cerr << "Number out of range: " << orr.what() << '\n';
                return 0;
            }
        }

        // Recursively evaluate left and right children and apply the operator
        double leftValue = evaluateNode(node->left);
        double rightValue = evaluateNode(node->right);

        if (node->value == "+") return leftValue + rightValue;
        if (node->value == "-") return leftValue - rightValue;
        if (node->value == "*") return leftValue * rightValue;
        return leftValue / rightValue; // Assume no division by zero 
    }

    // Function to construct the tree from a string 
    unique_ptr<Node> buildTree(const string& expr) {
        stack<int> opStack; // Stack to manage open parenthesis 
        vector<int> ops; // Vector to store operator positions 
        string cleanExpr = removeOuterParentheses(expr); // Sanitize the expression by removing outer parentheses
        int len = cleanExpr.length(); // Length of the cleaned expression 
        map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} }; // Map to store operator precedence 

        // Loop through the expression to find operators outside of any parentheses
        for (int i = 0; i < len; i++) {
            if (cleanExpr[i] == '(') opStack.push(i);
            else if (cleanExpr[i] == ')') opStack.pop();
            else if (opStack.empty() && precedence.find(cleanExpr[i]) != precedence.end()) {
                ops.push_back(i);
            }
        }

        if (ops.empty()) return make_unique<Node>(cleanExpr); // If no operators, return node with value

        int opIndex = selectOperator(cleanExpr, ops, precedence); // Select operator with highest precedence
        auto node = make_unique<Node>(string(1, cleanExpr[opIndex])); // Create node for operator
        node->left = buildTree(cleanExpr.substr(0, opIndex)); // Recursively build left subtree
        node->right = buildTree(cleanExpr.substr(opIndex + 1)); // Recursively build right subtree
        return node;
    }

    // Function to sanitize the expression by removing unnecessary parentheses
    string removeOuterParentheses(const string& expr) {
        if (expr.front() == '(' && expr.back() == ')') {
            return expr.substr(1, expr.length() - 2);
        }
        return expr;
    }

    // Function to select the operator with the highest precedence 
    int selectOperator(const string& expr, const vector<int>& ops, const map<char, int>& precedence) {
        int maxPrec = 0;
        int selectedIndex = 0;

        for (int index : ops) {
            int prec = precedence.at(expr[index]);
            if (prec > maxPrec) {
                maxPrec = prec;
                selectedIndex = index;
            }
        }
        return selectedIndex;
    }

    // Function to calculate the depth of the tree 
    int calculateDepth(Node* node) {
        if (!node) return 0;
        return 1 + max(calculateDepth(node->left.get()), calculateDepth(node->right.get()));
    }

    // Function to calculate the required width for display based on depth 
    int calculateWidth(int depth) {
        return (1 << depth) - 1; // Equivalent to 2^depth - 1 
    }

    // Recursive function to fill lines with node values for display 
    void fillDisplay(vector<string>& lines, Node* node, int row, int col, int depth) {
        if (!node || row >= depth) return;

        int branchLength = (1 << (depth - row - 2)); // Calculate branch length for spacing
        lines[row][col] = node->value[0]; // Place node value in the correct position

        if (node->left) {
            fillDisplay(lines, node->left.get(), row + 1, col - branchLength, depth); // Recursively display left child 
        }
        if (node->right) {
            fillDisplay(lines, node->right.get(), row + 1, col + branchLength, depth); // Recursively display right child 
        }
    }
};

int main() {
    ExTree exprTree; // Create an instance of ExTree 
    string expression = "(3+2)*5"; // Define the expression to be parsed and evaluated
    exprTree.constTree(expression); // Build the expression tree 

    cout << "Expression Tree Display:" << endl;
    exprTree.display(); // Display the tree 

    cout << "Evaluated Result: " << exprTree.evaluate() << endl; // Evaluate and display the result

    return 0;
}

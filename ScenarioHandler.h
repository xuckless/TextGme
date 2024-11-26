// ScenarioHandler.h
// Template class for handling decision tree scenarios in the game.
// Manages a tree structure where each node represents a scene or decision point.

#ifndef SCENARIOHANDLER_H
#define SCENARIOHANDLER_H

#include "Scenes.h"
#include <string>
#include <iostream>
#include <queue> // For BFS (Breadth-First Search)

template <typename T>
class ScenarioHandler {
public:
    Scenes<T>* root;           // Root node of the decision tree.
    Scenes<T>* currentNode;    // Pointer to the current node (for tracking player progress).

    // Constructor: Initializes the tree with a root node containing the given data.
    ScenarioHandler(T rootData);

    // Adds a child node to the specified parent node with the given data.
    Scenes<T>* addChild(Scenes<T>* parent, T childData);

    // Links an existing child node to the specified parent node.
    Scenes<T>* linkChild(Scenes<T>* parent, Scenes<T>* link);

    // Sets the current node (for tracking progress or navigating the tree).
    void setCurrentNode(Scenes<T>* node);

    // Returns the current node.
    Scenes<T>* getCurrentNode();

    // Prints the tree recursively from the given node (with optional prefix for formatting).
    void printTree(Scenes<T>* node, std::string prefix = "");

    // Overloaded method to print the entire tree starting from the root.
    void printTree();

    // Finds and returns a child node by its data using a breadth-first search.
    Scenes<T>* getChildByData(const T& data);
};

// Constructor: Creates the root node and sets it as the current node.
template <typename T>
ScenarioHandler<T>::ScenarioHandler(T rootData) {
    root = new Scenes<T>(rootData); // Initialize the root node.
    currentNode = root;            // Set the current node to root.
}

// Adds a new child node with the specified data to the given parent node.
// Returns a pointer to the newly created child node.
template <typename T>
Scenes<T>* ScenarioHandler<T>::addChild(Scenes<T>* parent, T childData) {
    Scenes<T>* childNode = new Scenes<T>(childData);
    parent->addChild(childNode); // Add the child to the parent's children.
    return childNode;
}

// Links an existing child node to a parent node (no new memory allocation).
// Returns a pointer to the linked node.
template <typename T>
Scenes<T>* ScenarioHandler<T>::linkChild(Scenes<T>* parent, Scenes<T>* link) {
    parent->addChild(link); // Add the link as a child of the parent.
    return link;
}

// Sets the current node for tracking or navigating the tree.
template <typename T>
void ScenarioHandler<T>::setCurrentNode(Scenes<T>* node) {
    currentNode = node; // Update the current node pointer.
}

// Returns the current node pointer.
template <typename T>
Scenes<T>* ScenarioHandler<T>::getCurrentNode() {
    return currentNode;
}

// Recursive helper function to print the tree starting from the given node.
// Each level is indented using the provided prefix for better visualization.
template <typename T>
void ScenarioHandler<T>::printTree(Scenes<T>* node, std::string prefix) {
    static int counter = 0; // Prevent infinite recursion (in case of loops).
    if (node == nullptr) return; // Base case: Null node.

    if (counter == 180) return; // Safeguard against excessive recursion depth.
    counter++;

    // Print the current node's data with the prefix for indentation.
    std::cout << prefix << node->data << std::endl;

    // Recursively print all child nodes with an additional "--" prefix.
    for (size_t i = 0; i < node->getChildren().size(); i++) {
        printTree(node->getChildren()[i], prefix + "--");
    }
}

// Overloaded method to print the entire tree starting from the root.
template <typename T>
void ScenarioHandler<T>::printTree() {
    printTree(root, ""); // Start from the root with no prefix.
}

// Performs a breadth-first search (BFS) to find a node with the given data.
// Returns a pointer to the found node, or nullptr if no matching node is found.
template <typename T>
Scenes<T>* ScenarioHandler<T>::getChildByData(const T& data) {
    std::queue<Scenes<T>*> q; // Queue for BFS traversal.
    q.push(root); // Start from the root.

    while (!q.empty()) {
        Scenes<T>* current = q.front(); // Get the next node.
        q.pop();

        if (current->data == data) { // Check if the data matches.
            return current;
        }

        // Enqueue all children of the current node for further traversal.
        for (auto child : current->getChildren()) {
            q.push(child);
        }
    }

    return nullptr; // Return nullptr if no match is found.
}

#endif // SCENARIOHANDLER_H
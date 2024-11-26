// Scenes.h
// Template class representing a single node in a decision tree or scenario graph.
// Each node contains data, a parent pointer, and a list of child nodes.

#ifndef SCENES_H
#define SCENES_H

#include <vector>

template <typename T>
class Scenes {
public:
    T data; // Data associated with this scene.
    std::vector<Scenes<T>*> children; // List of child nodes (next possible scenes).
    Scenes<T>* parent; // Pointer to the parent node (for backtracking).
    bool actionExecuted; // Flag to indicate if the action for this scene has been executed.

    // Constructor: Initializes the node with data.
    Scenes(T data);

    // Destructor: Recursively deletes all child nodes.
    ~Scenes();

    // Adds a child node to this scene.
    void addChild(Scenes<T>* child);

    // Returns the parent node of this scene.
    Scenes<T>* getParent();

    // Returns a reference to the list of child nodes.
    std::vector<Scenes<T>*>& getChildren();
};

// Constructor: Initializes the scene with the given data, sets the parent to nullptr,
// and initializes the actionExecuted flag to false.
template <typename T>
Scenes<T>::Scenes(T data) : data(data), parent(nullptr), actionExecuted(false) {}

// Destructor: Deletes all child nodes recursively to free memory.
template <typename T>
Scenes<T>::~Scenes() {
    for (auto child : children) {
        delete child; // Recursively delete each child node.
    }
}

// Adds a child node to the current scene and sets the parent of the child to this node.
template <typename T>
void Scenes<T>::addChild(Scenes<T>* child) {
    child->parent = this; // Set the parent pointer of the child.
    children.push_back(child); // Add the child to the list of children.
}

// Returns the parent node of this scene.
template <typename T>
Scenes<T>* Scenes<T>::getParent() {
    return parent;
}

// Returns a reference to the vector of child nodes.
template <typename T>
std::vector<Scenes<T>*>& Scenes<T>::getChildren() {
    return children;
}

#endif // SCENES_H
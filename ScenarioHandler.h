#ifndef SCENARIOHANDLER_H
#define SCENARIOHANDLER_H

#include "Scenes.h"
#include <string>
#include <iostream>

template <typename T>
class ScenarioHandler {
public:
    Scenes<T>* root;
    Scenes<T>* currentNode; // Pointer to track the current node

    ScenarioHandler(T rootData);

    Scenes<T>* addChild(Scenes<T>* parent, T childData);
    Scenes<T>* linkChild(Scenes<T>* parent, Scenes<T>* link);
    void setCurrentNode(Scenes<T>* node); // New method to set current node
    Scenes<T>* getCurrentNode(); // New method to get the current node
    void printTree(Scenes<T>* node, std::string prefix = "");
    void printTree();
};

template <typename T>
ScenarioHandler<T>::ScenarioHandler(T rootData) {
    root = new Scenes<T>(rootData);
    currentNode = root; // Initialize current node to root
}

template <typename T>
Scenes<T>* ScenarioHandler<T>::addChild(Scenes<T>* parent, T childData) {
    Scenes<T>* childNode = new Scenes<T>(childData);
    parent->addChild(childNode);
    return childNode;
}

template <typename T>
Scenes<T>* ScenarioHandler<T>::linkChild(Scenes<T>* parent, Scenes<T>* link) {
    parent->addChild(link);
    return link;
}

template <typename T>
void ScenarioHandler<T>::setCurrentNode(Scenes<T>* node) {
    currentNode = node; // Update the current node
}

template <typename T>
Scenes<T>* ScenarioHandler<T>::getCurrentNode() {
    return currentNode; // Return the current node
}

template <typename T>
void ScenarioHandler<T>::printTree(Scenes<T>* node, std::string prefix) {
    static int counter = 0;
    if (node == nullptr) return;

    if (counter == 180) return;
    counter++;

    std::cout << prefix << node->data << std::endl;

    for (size_t i = 0; i < node->getChildren().size(); i++) {
        printTree(node->getChildren()[i], prefix + "--");
    }
}

template <typename T>
void ScenarioHandler<T>::printTree() {
    printTree(root, "");
}

#endif // SCENARIOHANDLER_H

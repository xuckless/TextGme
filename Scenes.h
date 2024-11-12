// Scenes.h
#ifndef SCENES_H
#define SCENES_H

#include <vector>

template <typename T>
class Scenes {
public:
    T data;
    std::vector<Scenes<T>*> children;
    Scenes<T>* parent;
    bool actionExecuted; // New flag to indicate if the action has been executed

    Scenes(T data);
    ~Scenes();

    void addChild(Scenes<T>* child);
    Scenes<T>* getParent();
    std::vector<Scenes<T>*>& getChildren();
};

template <typename T>
Scenes<T>::Scenes(T data) : data(data), parent(nullptr), actionExecuted(false) {}

template <typename T>
Scenes<T>::~Scenes() {
    for (auto child : children) {
        delete child;
    }
}

template <typename T>
void Scenes<T>::addChild(Scenes<T>* child) {
    child->parent = this;
    children.push_back(child);
}

template <typename T>
Scenes<T>* Scenes<T>::getParent() {
    return parent;
}

template <typename T>
std::vector<Scenes<T>*>& Scenes<T>::getChildren() {
    return children;
}

#endif // SCENES_H

//
// Created by carba on 30/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_NODE_H
#define CARLOSBADILLAARIAS_PROYECTO2_NODE_H

#include <memory>
using namespace std;

//Here the node class is declared and a template is used, which is why it doesn't have a .cpp file.
//It's also important to know that T must be a pointer, for example, Item*
template <typename T>
class Node {
public:
    T data;
    shared_ptr<Node<T>> next;
    explicit Node(T data) : data(data), next(nullptr){}
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_NODE_H

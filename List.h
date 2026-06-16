//
// Created by carba on 30/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_LIST_H
#define CARLOSBADILLAARIAS_PROYECTO2_LIST_H

#include <string>
#include <stdexcept>
#include <memory>
#include "Node.h"
using namespace std;

template <typename T>
class List {
private:
    shared_ptr<Node<T>> ppio;
    int size;
public:
    List():ppio(nullptr),size(0){}

    //This is to add an element at the end
    void add(T item) {
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(item);
        if (ppio == nullptr) {
            ppio = newNode;
        }
        else {
            shared_ptr<Node<T>> current = ppio;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    //Aqui lo que se hace es remover por indice y devolver los datos
    T removeAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Indice de la lista fuera de rango: " + to_string(index));
        }
        T removed;
        if (index == 0) {
            removed = ppio->data;
            ppio = ppio->next;
        }
        else {
            shared_ptr<Node<T>> current = ppio;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            removed = current->next->data;
            current->next = current->next->next;  // fix: era ->data
        }
        size--;
        return removed;
    }

    //obtener elemento por indice
    T get(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Indice de la lista fuera de rango: " + to_string(index));
        }
        shared_ptr<Node<T>> current = ppio;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    //Encontrar el indice de un elemento que coincida con una condicion, si no lo encuentra devuelve -1
    int findif(bool(*predicate)(T)) const {
        shared_ptr<Node<T>> current = ppio;
        int index = 0;
        while (current != nullptr) {
            if (predicate(current->data)) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    bool isEmpty() const {
        if (size == 0) {
            return true;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    //Soporte para iterador range-based for
    class Iterator {
    private:
        shared_ptr<Node<T>> current;  // fix: era share_ptr
    public:
        explicit Iterator(shared_ptr<Node<T>> node) : current(node) {}  // fix: era current(Node)

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;  // fix: faltaba la asignacion
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(ppio);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_LIST_H
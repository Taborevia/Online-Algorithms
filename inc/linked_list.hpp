#ifndef LL_H
#define LL_H

#include <iostream>
#include <memory>

class Node {
public:
    int value;
    int counter;
    std::unique_ptr<Node> next;
    
    Node(int val);
};

class linked_list {
public:
    std::unique_ptr<Node> head;
    int self_organization;

    linked_list(int self_organization_type); //0 - without organization, 1 - Move to front, 2-transpose,3-count
    int access(int value);
    void print();
};

#endif
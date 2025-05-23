#include "linked_list.hpp"

Node::Node(int val) : value(val), next(nullptr), counter(0) {}
linked_list::linked_list(int self_organization_type) : self_organization(self_organization_type) {}
int linked_list::access(int value) {
    int cost=2;
    bool found = false;
    Node* prev = nullptr;
    Node* current = head.get();
    if (!head) {
        head = std::make_unique<Node>(value);
        return 1;
    }
    if (current->value==value){
        current->counter++;
        return 1;
    }
    while (current->next) {
        if (current->next->value == value) {
            found = true;
            switch(self_organization){
                case 0:
                    break;
                case 1:{ //Move to front
                    std::unique_ptr<Node> temp = std::move(current->next);
                    current->next = std::move(temp->next);
                    temp->next = std::move(head);
                    head = std::move(temp);
                    break;
                }
                case 2:{//transposition
                    if(prev){
                        std::unique_ptr<Node> temp = std::move(current->next);
                        current->next = std::move(temp->next);
                        temp->next = std::move(prev->next);
                        prev->next = std::move(temp);
                    }else{
                        std::unique_ptr<Node> temp = std::move(current->next);
                        head->next = std::move(temp->next);
                        temp->next = std::move(head);
                        head = std::move(temp);
                    }
                    break;
                }
                case 3:
                    current->next->counter++;
                    Node* current_case_3 = head.get();
                    if(current->next->counter>=head->counter){
                        std::unique_ptr<Node> temp = std::move(current->next);
                        current->next = std::move(temp->next);
                        temp->next = std::move(head);
                        head = std::move(temp);
                    }else{
                        while(true){
                            if (current_case_3->next->counter<=current->next->counter){
                                break;
                            }
                            current_case_3 = current_case_3->next.get();
                        }
                        std::unique_ptr<Node> temp = std::move(current->next);
                        current->next = std::move(temp->next);
                        temp->next = std::move(current_case_3->next);
                        current_case_3->next = std::move(temp);
                    }
                    break;
            }
            break;
        }
        cost++;
        prev = current;
        current = current->next.get();
    }
    if(!found){
        current->next = std::make_unique<Node>(value);
    }
    return cost;
}

void linked_list::print() {
    Node* current = head.get();
    while (current) {
        if(self_organization==3){
            std::cout << current->value <<","<<current->counter<< " -> ";
        }else{
            std::cout << current->value << " -> ";
        }
        current = current->next.get();
    }
    std::cout << "nullptr" << std::endl;
}

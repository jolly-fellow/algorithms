//
// Created by alex on 5/21/21.
//

#include "list.hpp"
#include <iostream>
#include <vector>

namespace algorithms::list {
    using namespace std;

    // Node of a double linked list
    struct Node_DLL {
        Node_DLL * prev;
        Node_DLL * next;
        int data;
    };

    // Node of a single linked list
    struct Node_SLL {
        Node_SLL * next;
        int data;
    };

    // Create a single linked list from a vector
    Node_SLL * make_sl_list(const vector<int> & list) {

        size_t list_size = list.size();

        if(list_size == 0) { return nullptr; }

        Node_SLL * head = new Node_SLL;

        head->next = nullptr;
        head->data = list[0];

        Node_SLL * tail = head;

        for(int i = 1; i < list_size; ++i ) {
            Node_SLL * node = new Node_SLL;
            tail->next = node;
            node->data = list[i];
            tail = node;
        }
        return head;
    }


    Node_DLL * make_dl_list(const vector<int> & list) {

        size_t list_size = list.size();

        if(list_size == 0) { return nullptr; }

        Node_DLL * head = new Node_DLL;

        head->prev = nullptr;
        head->next = nullptr;
        head->data = list[0];

        Node_DLL * tail = head;

        for(int i = 1; i < list_size; ++i ) {
            Node_DLL * node = new Node_DLL;
            tail->next = node;
            node->prev = tail;
            node->data = list[i];
            tail = node;
        }
        return head;
    }

    void print_list(Node_DLL * list) {
        while(list != nullptr) {
            cout << list->data << " ";
            list = list->next;
        }
    }

    void print_list(Node_SLL * list) {
        while(list != nullptr) {
            cout << list->data << " ";
            list = list->next;
        }
    }

    //
    void remover_dll(Node_DLL * list, int to_remove, bool remove_one = false) {
        if(list == nullptr) { return; }

        do {
            Node_DLL * curr = list;
            if(curr->data == to_remove) {
                if(curr->prev != nullptr) {
                    curr->prev->next = curr->next;
                }

                if(curr->next != nullptr) {
                    curr->next->prev = curr->prev;
                }
                list = curr->next;
                delete curr;
                if(remove_one == true) {
                    return;
                }
            }
            else {
                list = list->next;
            }
        } while(list != nullptr);
    }

    Node_SLL *remover_sll(Node_SLL *head, int to_remove, bool remove_one = false) {

        Node_SLL *curr = head;
        Node_SLL *prev = nullptr;

        while (curr != nullptr) {
            if (curr->data == to_remove) {
                Node_SLL *temp = curr;
                if (prev == nullptr) { // this is a head
                    curr = curr->next;
                    delete temp;
                } else {
                    prev->next = curr->next;
                    delete curr;
                    curr = prev;
                    if (remove_one == true) {
                        return head;
                    }
                }

            }
            prev = curr;
            curr = curr->next;
        }
        return head;
    }


    void test() {

        cout << "\nlist test" << endl;

        cout << "\nMake double linked list" << endl;

        Node_DLL * n = make_dl_list({1, 2, 3, 3, 3, 4, 5, 5, 5});

        print_list(n);

        cout << endl << "remove element with data = 5" << endl;

        remover_dll(n, 5, true);

        cout << "\nResult:" << endl;

        print_list(n);

        cout << endl;

        cout << "\nMake single linked list" << endl;

        Node_SLL * sll = make_sl_list({1, 2, 3, 3, 3, 4, 5, 5, 5});

        print_list(sll);

        cout << endl << "remove element with data = 5" << endl;

        remover_sll(sll, 5, true);

        cout << "\nResult:" << endl;

        print_list(sll);

        cout << endl;


    }
}
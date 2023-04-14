#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <cassert>

#include "../node/node.h"

using namespace std;

// Declaration
//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T>* head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this);

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>* &head, node<T>* after_this, T insert_this);

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>* &head, node<T>* delete_this);

//duplicate the list
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T>* src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>* &head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//Last node in the list, never use this function.
template <typename T>
node<T>* _last_node(node<T>* head);



// Definition
template <typename T>
void _print_list(node<T>* head){
    if(head == nullptr){
        return;
    }
    while(head != nullptr){
        cout << *head;
        head = head->_next;
    }
    cout << "|||\n";
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T>* head){
    //stops recursive function at last link.
    if(head == nullptr)
        return;
    // will continue calling until head is last.
    _print_list_backwards(head->_next);
    //only prints if last linked list is found
    cout << head;
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    while(head != nullptr){
        if(head->_item == key){
            return head;
        }
        head = head->_next;
    }
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this){
    node<T>* tempNode = new node<T>; 
    tempNode->_item = insert_this;
    tempNode->_next = head;
    head = tempNode;
    return head; // ask about this?
}

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>* &head, node<T>* after_this, T insert_this){
    if(head == nullptr){
        return _insert_head(head, insert_this);
    }
    node<T>* tempNode = new node<T>;
    tempNode->_item = insert_this;
    tempNode->_next = after_this->_next;

    after_this->_next = tempNode;
    return tempNode; //or head? 
}

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this){
    if(before_this == head){
        return _insert_head(head, insert_this);
    }
    node<T>* tempNode = new node<T>;
    tempNode->_item = insert_this;

    node<T>* nodeWalker = head;
    while(nodeWalker != nullptr){
        if(nodeWalker->_next == before_this){
            tempNode->_next = nodeWalker->_next;
            nodeWalker->_next = tempNode;
            return tempNode;
        }
        nodeWalker = nodeWalker->_next;
    }
   return nullptr; // if fails?
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this){ 
    if(prev_to_this == head){
        return nullptr; // right? correct?
    }
    while(head != nullptr){
        if(head->_next == prev_to_this){
            return head;
        }
        head = head->_next;
    }
    return nullptr;
}

// first think about if head is null
// if you do somehting on head any special
// if you do anything about tail, any special
// if you do anything in the middle??

//delete, return item
template <typename T>
T _delete_node(node<T>* &head, node<T>* delete_this){
    assert(head != nullptr);
    node<T>* nodeWalker = head;
    T itemCopy;

    if(delete_this == head){
        itemCopy = head->_item;
        head = head->_next;
        delete nodeWalker;
        return itemCopy;
    }

    node<T>* previous = nodeWalker;
    nodeWalker = head->_next;
    while(nodeWalker != nullptr){
        if(nodeWalker == delete_this){
            itemCopy = nodeWalker->_item;
            previous->_next = nodeWalker->_next;
            delete nodeWalker;
            return itemCopy;
        }
        previous = nodeWalker;
        nodeWalker = nodeWalker->_next;
    }
    assert(nodeWalker != nullptr);
    return T();
}

//duplicate the list
template <typename T>
node<T>* _copy_list(node<T>* head){
    if(head == nullptr){
        return nullptr;
    }
    node<T>* copyList = new node<T>;
    copyList->_item = head->_item;

    node<T>* newHead = copyList;
    while(head->_next != nullptr){
        copyList->_next = new node<T>;
        copyList = copyList->_next;
        head = head->_next;
        copyList->_item = head->_item;
    }
    copyList->_next = nullptr;
    return newHead;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T>* src){
    if(src == nullptr){
        return nullptr;
    }
    node<T>* copyList = new node<T>;
    copyList->_item = src->_item;

    node<T>* newHead = copyList;
    while(src->_next != nullptr){
        copyList->_next = new node<T>;
        copyList = copyList->_next;
        src = src->_next;
        copyList->_item = src->_item;
    }
    dest = copyList;
    copyList->_next = nullptr;
    return newHead;
}

// TODO
// traverse link list , before deleting remember the next node and delete the current one. 
//delete all the nodes
template <typename T>
void _clear_list(node<T>* &head){
    if(head == nullptr){
        return;
    }
    node<T>* nodeWalker = head;
    while(nodeWalker != nullptr){
        node<T>* nextNode = nodeWalker->_next;
        delete nodeWalker;
        nodeWalker = nextNode;
    }
    head = nullptr;
}

//traverse until the last one.....

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    int index = 0;
    while(head != nullptr){
        if(index == pos){
            return head->_item;
        }
        head = head->_next;
        index++;
    }
    assert(0);
    return head->_item;
}

//Last node in the list, never use this function.
template <typename T>
node<T>* _last_node(node<T>* head){
    while(head->_next != nullptr){
        head = head->_next;
    }
    return head;
}

#endif // LINKED_LIST_FUNCTIONS_H
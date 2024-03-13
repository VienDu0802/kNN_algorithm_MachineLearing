#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */


////////////////////////////////////////////////////////////////
//                        Class Node                          //
////////////////////////////////////////////////////////////////

template <typename T>
Node<T>::Node(T val) : value(val), prev(nullptr), next(nullptr) {}

template <typename T>
Node<T>::Node(T val, Node<T> *prevNode, Node<T> *nextNode) : value(val), prev(prevNode), next(nextNode) {}

// template<typename T>
// T Node<T>::getValue() const {
//     return value;
// }

// template<typename T>
// void Node<T>::setValue(T val){
//     value = val;
// }

// template <typename T>
// Node<T>* Node<T>:: getPrev() const {
//     return prev;
// }

// template <typename T>
// void Node<T>::setPrev(Node<T>* prevNode)
// {
//     prev = prevNode;
// }

// template <typename T>
// Node<T> *Node<T>::getNext() const
// {
//     return next;
// }

// template <typename T>
// void Node<T>::setNext(Node<T>* nextNode)
// {
//     next = nextNode;
// }

////////////////////////////////////////////////////////////////
//                     Class DLinkedList                      //
////////////////////////////////////////////////////////////////

template <typename T>
DLinkedList<T>::DLinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
void DLinkedList<T>::push_back(T value) {
    Node *newNode = Node(value);
    if (tail)
    {
        tail->next = newNode;
        tail = tail->next;
    }
    else
    {
        head = tail = newNode;
    }

    count++;
}

template <typename T>
void DLinkedList<T>::push_front(T value){
    Node<T>* newNode = new Node(value);
    if(head){
        head->prev = newNode;
    }else{
        tail = newNode;
    }
    head = newNode;
    count++;
}

template <typename T>
void DLinkedList<T>::insert(int index, T value){
    if (index < 0 || index > count)
    {
        cout << "Invalid index";
        return;
    }
    else if(index == 0){
        push_front(value);
    }
    else if(index == count){
        push_back(value);
    }else{
        Node<T>* curr = head;
        Node<T>* newNode = new Node(value);
        for(int i=0; i<index-1; count++){
            curr = curr->next;
        }
        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next = newNode;
        curr->next->prev = newNode;
        count++;
    }

}

template <typename T>
void DLinkedList<T>::remove(int index){
    if(index<0 || index>count){
        cout <<"Invalid index";
        return;
    }
    
    Node<T>* curr = head;
    if(index == 0){
        if(head){
            head = head->next;
            head->prev=nullptr;
        }else{
            tail = nullptr;
        }
    }else if(index == count){
        if(tail){
            tail = tail->prev;
            tail->next = nullptr;
        }else{
            head = nullptr;
        }
    }
    else{
        Node<T>* curr = head;
        for(int i=0;i<index;i++){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        if(curr->next) {    
            curr->next->prev = curr->prev;
        }
        else tail = curr->prev;
    }
    delete curr;
    count--;
}

template <typename T>
T &DLinkedList<T>::get(int index) const {
    
}

////////////////////////////////////////////////////////////////
//                      Class Dataset                         //
////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////
//                        Class kNN                           //
////////////////////////////////////////////////////////////////
void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    this->X_train = X_train;
    this->y_train = y_train;
}

Dataset kNN::predict(const Dataset& X_test){
    Dataset y_pred;
    //tinh toan khoang cach va chon k gan nhat
    //
    //
    //
    return y_pred;
}
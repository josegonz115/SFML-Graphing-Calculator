#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Queue;

    //Default CTOR
    Iterator():_ptr(nullptr){}
    //Point Iterator to where p is pointing to
    Iterator(node<T>* p):_ptr(p){}

    //Casting operator: true if _ptr not NULL
    //This turned out to be a pain!
    operator bool() { return _ptr; }

    //dereference operator
    T& operator *(){ return _ptr->_item; }  
    //member access operator
    T* operator ->(){ return this;  }
    //true if _ptr is NULL
    bool is_null(){ return !_ptr; }   

    //true if left != right
    friend bool operator !=(const Iterator &left, const Iterator &right){ 
        return left._ptr != right._ptr;
    }
    //true if left == right
    friend bool operator ==(const Iterator &left, const Iterator &right){
        return left._ptr == right._ptr;
     }

    //member operator:  ++it; or ++it = new_value
    Iterator& operator ++(){ 
        _ptr = _ptr->_next;
        return *this;
    }                 
    //friend operator: it++
    friend Iterator operator ++(Iterator &it, int unused){
        Iterator temp;
        temp = it;
        it._ptr = it._ptr->_next;
        return temp;
     }

  private:
    node<T>* _ptr; //pointer being encapsulated
  };

  //constructor: CTOR
  Queue();

  //BIG 3:
  Queue(const Queue<T>& copyMe);
  ~Queue();
  Queue<T>& operator =(const Queue<T>& RHS);

  //Operations:
  void push(T item);                  //Enqueue
  T pop();                         //Dequeue

  //Accessors:
  Iterator begin() const;             //Iterator to the head node
  Iterator end() const;               //Iterator to NULL

  //Checkers:
  int size() const;
  bool empty();
  T front();
  T back();

  template<typename U>
  friend ostream& operator <<(ostream& outs, const Queue<U>& printMe);
  
private:
  node<T>* _front;
  node<T>* _rear;
  int _size;
};


//Definition
//constructor: CTOR
template <typename T>
Queue<T>::Queue():_front(nullptr), _rear(nullptr), _size(0){}

//BIG 3:----------------------------------------------------
template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = _copy_list(copyMe._front);
    _rear = _last_node(_front);
    _size = copyMe._size;
}

template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front); //deletes memory for _rear too
}

template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& RHS){
    if(this == &RHS){
        return *this;
    }
    _front = _copy_list(RHS._front);
    _rear = _last_node(_front);
    _size = RHS._size;
    return *this;
}

//Operations:-----------------------------------------------
//Enqueue
template <typename T>
void Queue<T>::push(T item){
    // no max
    _size++;
    _rear = _insert_after(_front, _rear, item);
    //_rear = _rear->_next;
}                  

//Dequeue
template <typename T>
T Queue<T>::pop(){
    if(empty()){
        return T();
    }
    _size--;
    T item = _front->_item;
    _delete_node(_front, _front);
    return item;
}                 

//Accessors:------------------------------------------------
//Iterator to the head node
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return Iterator(_front);
}          

template <typename T>
//Iterator to NULL
typename Queue<T>::Iterator Queue<T>::end() const{
    return Iterator(_rear->_next);
}             


//Checkers:-------------------------------------------------
template <typename T>
int Queue<T>::size() const{
    return _size;
}

template <typename T>
bool Queue<T>::empty(){
    return _size == 0;
}

template <typename T>
T Queue<T>::front(){
    return _front->_item;
}

template <typename T>
T Queue<T>::back(){
    return _rear->_item;
}
//----------------------------------------------------------
template<typename U>
ostream& operator <<(ostream& outs, const Queue<U>& printMe){
    node<U>* nodeWalker = printMe._front;
    for(int i = 0; i < printMe._size; i++){
        outs << *nodeWalker;
        nodeWalker = nodeWalker->_next;
    }
    if(nodeWalker == printMe.end()){
        outs << "|||\n";
    }
    return outs;
}


#endif //MYQUEUE_H
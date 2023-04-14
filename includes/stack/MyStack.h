#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Stack;

    //Default CTOR
    Iterator():_ptr(nullptr){}
    //Point Iterator to where p is pointing to
    Iterator(node<T>* p):_ptr(p){}

    //Casting operator: true if _ptr not NULL
    //This turned out to be a pain!
    operator bool() { return _ptr; }
    
    //dereference operator
    T& operator *(){ 
      assert(_ptr);
      return _ptr->_item; 
      }

    //member access operator
    T* operator ->(){
      assert(_ptr);
      return this; 
    }

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
      it._ptr= it._ptr->_next;
      return temp;
     }
    
  private:
    node<T>* _ptr; //pointer being encapsulated
  };

  //constructor: CTOR
  Stack();

  //BIG 3:
  Stack(const Stack<T>& copyMe);
  ~Stack();
  Stack<T>& operator =(const Stack<T>& RHS);

  //Operations:
  void push(T item);
  //void pop(); 
  T pop();

  //Accessors:
  Iterator begin() const;            //Iterator to the head node
  Iterator end() const;              //Iterator to NULL

  //Checkers:
  int size() const{ return _size; }
  bool empty(){ return _size == 0; }
  T top(){ return _top->_item; }

  template<typename U>
  friend ostream& operator <<(ostream& outs, const Stack<U>& printMe);

private:
  node<T>* _top;
  int _size;
};


//Definition
//Constructor
template <typename T>
Stack<T>::Stack():_top(nullptr), _size(0){}

//BIG 3---------------------------------------------
template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe){
  _top = _copy_list(copyMe._top);
  _size = copyMe._size;
}

template <typename T>
Stack<T>::~Stack(){
  _clear_list(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator =(const Stack<T>& RHS){
  if(this == &RHS){
    return *this;
  }
  _clear_list(_top);
  _top = _copy_list(RHS._top);
  _size = RHS._size;
  return *this;
}
//-------------------------------------------------

//Operations:
template <typename T>
void Stack<T>::push(T item){
  // no max
  _size++;
  _insert_head(_top, item);
}

template <typename T>
//void Stack<T>::pop(){
T Stack<T>::pop(){
  if(empty()){
    //return;
    assert(0);
  }
  _size--;
  //_delete_node(_top, _top);
  return _delete_node(_top, _top);
}

//Accessors:
//Iterator to the head node
template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const{
  return(Iterator(_top));
}

//Iterator to NULL
template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const{
  return(Iterator(_last_node(_top)->_next));
}            

template<typename U>
ostream& operator <<(ostream& outs, const Stack<U>& printMe){
  node<U>* nodeWalker = printMe._top;
  for(int i = 0; i < printMe._size; i++){
    outs << *nodeWalker;
    nodeWalker = nodeWalker->_next;
  }
  if(nodeWalker == printMe.end()){
    outs << "|||\n";
  }
  return outs;
}

#endif // MYSTACK_H
// IMPORTANT: Project specifications requires that List.h and List_tests.cpp to be
// the only submitted files.

// "For Fall 2021, the driver portion of the project that implements the web API (api.cpp) is OPTIONAL and is NOT GRADED on the autograder. The List.h and List_tests.cpp files are all that is required. You are still welcome to do the whole project if you like, or to return to it on your own after the course has finished. (We don’t necessarily expect it would be realistic to do it before the project deadline.)"

#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  List();

  List(const List &rhs);

  List & operator=(const List &rhs);

  ~List();

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

  int num_nodes;

public:
  ////////////////////////////////////////
  class Iterator {
    //friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:

    // EFFECTS: Constructs a past-the-end iterator.
    Iterator() : node_ptr(nullptr) {}

    Iterator(Iterator const &rhs){
      node_ptr = rhs.node_ptr;
    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*() const;

    Iterator &operator++();

    bool operator==(Iterator rhs) const;

    bool operator!=(Iterator rhs) const;

  private:
    // EFFECTS: Constructs an iterator from the given node pointer.
    //Iterator(Node *node_ptr_in) : node_ptr(node_ptr_in) {}

    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p){
      node_ptr = p;
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    assert(i.node_ptr);

    Node *victim = i.node_ptr;

    if (victim == first) {
      pop_front();
    }
    else if (victim == last){
      pop_back();
    }
    else{
        Node *left = victim->prev;
        Node *right = victim->next;
    
        left->next = right;
        right->prev = left;
        delete victim;
        --num_nodes;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    Node *new_node = new Node;
    new_node->datum = datum;
    new_node->next = nullptr;
    new_node->prev = nullptr;
    if (empty()){
      first = last = new_node;
      ++num_nodes;
      return;
    }

    Node *current_node = i.node_ptr;

    if (current_node == first){
      push_front(datum);
    }
    else if (current_node == nullptr){
      push_back(datum);
    }
    else{
    new_node->next = current_node;
    new_node->prev = current_node->prev;
    current_node->prev->next = new_node;
    current_node->prev = new_node;
    
    ++num_nodes;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

template<typename T>
List<T>::List() : first(nullptr), last(nullptr), num_nodes(0) {}

template<typename T>
List<T>::List(const List &other) : List() {
  copy_all(other);
}

template<typename T>
List<T> & List<T>::operator=(const List &rhs) {
  if (this != &rhs) {
    while (!empty()) {
      pop_front();
    }
    copy_all(rhs);
  }
  return *this;
}

template<typename T>
List<T>::~List() {
  while (!empty()) {
    pop_front();
  }
}

template<typename T>
bool List<T>::empty() const {
  return first == nullptr;
}

template<typename T>
int List<T>::size() const {
  return num_nodes;
}

template<typename T>
T& List<T>::front() {
  assert(!empty());
  return first->datum;
}

template<typename T>
T& List<T>::back() {
  assert(!empty());
  return last->datum;
}

template<typename T>
void List<T>::push_front(const T &datum) {
  Node *new_node = new Node;
  new_node->datum = datum;
  new_node->next = first;
  new_node->prev = nullptr;

  if (empty()) {
    first = last = new_node;
  } else {
    first = first->prev = new_node;
  }
  ++num_nodes;
}

template<typename T>
void List<T>::push_back(const T &datum) {
  Node *new_node = new Node;
  new_node->datum = datum;
  new_node->next = nullptr;
  new_node->prev = last;

  if (empty()) {
    first = last = new_node;
  } else {
    last = last->next = new_node;
  }
  ++num_nodes;
}

template<typename T>
void List<T>::pop_front() {
  assert(!empty());
  Node *victim = first;           // temporary keeps track of old first
  if (size() > 1){
    first = first->next;
    first->prev = nullptr;
  }
  else {
    first = nullptr;
    last = nullptr;
  }
  delete victim;
  --num_nodes;
}

template<typename T>
void List<T>::pop_back() {
  assert(!empty());
  Node *victim = last;           // temporary keeps track of old last
  if (size() > 1){
    last = last->prev;
    last->next = nullptr;
  }
  else{
    first = nullptr;
    last = nullptr;
  }
  delete victim;
  --num_nodes;
}

template<typename T>
void List<T>::clear() {
  while(!empty()){
    pop_front();
  }
}

template<typename T>
void List<T>::copy_all(const List<T> &other) {
  assert(empty());
  num_nodes = 0;
  for (Node *node_ptr = other.first; node_ptr; node_ptr = node_ptr->next) {
    push_back(node_ptr->datum);
  }
}

template <typename T>
T & List<T>::Iterator::operator*() const {
  assert(node_ptr);  // check whether this is a past-the-end iterator
  return node_ptr->datum;
}

template <typename T>
typename List<T>::Iterator & List<T>::Iterator::operator++() {
  assert(node_ptr);  // check whether this is a past-the-end iterator
  node_ptr = node_ptr->next;
  return *this;
}

template <typename T>
bool List<T>::Iterator::operator==(Iterator rhs) const {
  return node_ptr == rhs.node_ptr;
}

template <typename T>
bool List<T>::Iterator::operator!=(Iterator rhs) const {
  return node_ptr != rhs.node_ptr;
}


#endif // Do not remove this. Write all your code above this line.

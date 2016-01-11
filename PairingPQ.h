#ifndef PAIRING_H
#define PAIRING_H

#include "Eecs281PQ.h"
#include <queue> 
#include <iostream>

using namespace std;

//A specialized version of the 'priority_queue' ADT implemented as a pairing priority_queue.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
private:
  int count;
public:
  typedef unsigned size_type;

  //Description: Construct a priority_queue out of an iterator range with an optional
  //             comparison functor.
  //Runtime: O(n) where n is number of elements in range.
  template<typename InputIterator>
  PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());

  //Description: Construct an empty priority_queue with an optional comparison functor.
  //Runtime: O(1)
  PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR());
  
  //Description: Copy constructor.
  //Runtime: O(n)
  PairingPQ(const PairingPQ& other);
  
  //Description: Copy assignment operator.
  //Runtime: O(n)
  PairingPQ& operator=(const PairingPQ& rhs);
  
  //Description: Destructor
  //Runtime: O(n)
  ~PairingPQ();

  //Description: Add a new element to the priority_queue.
  //Runtime: Amortized O(1)
  virtual void push(const TYPE& val);

  //Description: Remove the most extreme (defined by 'compare') element from
  //             the priority_queue.
  //Note: We will not run tests on your code that would require it to pop an
  //element when the priority_queue is empty. Though you are welcome to if you are
  //familiar with them, you do not need to use exceptions in this project.
  //Runtime: Amortized O(log(n))
  virtual void pop();

  //Description: Return the most extreme (defined by 'compare') element of
  //             the priority_queue.
  //Runtime: O(1)
  virtual const TYPE& top() const;

  //Description: Get the number of elements in the priority_queue.
  //Runtime: O(1)
  virtual size_type size() const { return count; }

  //Description: Return true if the priority_queue is empty.
  //Runtime: O(1)
  virtual bool empty() const { 
     if(root == nullptr) {
        return true;
     }
     return false;
  }
  class Node {
  public:
	Node(const TYPE & val)
	{
			elt = val;
			sibling = child = nullptr;
	}
  public:
    //Description: Allows access to the element at that Node's position.
    //Runtime: O(1) - this has been provided for you.
    const TYPE& operator*() const { return elt; }
    const Node* sibling_ptr() const { return sibling; }
    const Node* child_ptr() const { return child; }

    //The following line allows you to access any private data members of this
    //Node class from within the pairing_priority_queue class. (ie: myNode.elt is a legal
    //statement in PairingPQ's add_node() function).
    friend PairingPQ;
  private:
    TYPE elt;
    Node* sibling;
    Node* child; 
  };

  const Node* root_ptr() const { return root; }

private:
  Node* root;
  //***Add any additional member functions or data you require here.
  //***We recommend creating a 'meld' function (see the spec).
  Node* meld(Node* first, Node* second) {
    Node *current;
    if(this->compare(first->elt, second->elt)) { 
      current = second->child; 
      second->child = first;
      second->sibling = nullptr;
      first->sibling = current;
      return second;
    }
    else {
      current = first->child; 
      first->child = second;
      first->sibling = nullptr;
      second->sibling = current;
      return first;
    }
  }
  void destructorfunc() {
    queue<Node*> qtemp;
    if(root == nullptr) {
      return;
    }
    if(root->child != nullptr) {
      qtemp.push(root->child);
    } 
    else if(root->child == nullptr && root->sibling == nullptr) {
      delete root;
      return; 
    }
    delete root; 
    while(!qtemp.empty()) {
      Node *n = qtemp.front(); 
      qtemp.pop();
      if(n->child != nullptr) {
        qtemp.push(n->child); 
      }
      else if(n->sibling != nullptr) {
        qtemp.push(n->sibling);
      }
      delete n; 
    }
    count = 0;
  }
  
  void copy(Node* o) {
    queue<Node*> qtemp; 
    int temp;
    if(o != nullptr) {
      temp = o->elt; 
      Node *rootcp = new Node(temp);
      root = rootcp; 
      ++count;
      if(o->child != nullptr) {
        qtemp.push(o->child);
      } 
    }
    
    Node* current = o; 
    while(!qtemp.empty()) {
      temp = qtemp.front()->elt; 
      Node *n = new Node(temp);
      current = qtemp.front(); 
      root = meld(root, n); 
      ++count;
      qtemp.pop();
      if(current->child != nullptr) {
        qtemp.push(current->child); 
      }
      else if(current->sibling != nullptr) {
        qtemp.push(current->sibling);
      }
    }
  }
};

template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
PairingPQ<TYPE, COMP_FUNCTOR>::PairingPQ(
  InputIterator start,
  InputIterator end,
  COMP_FUNCTOR comp
) {
  this->compare = comp;
  count = 0;
  Node *rootcp = new Node(*start);
  root = rootcp;
  ++start;
  ++count;
  for(; start != end; ++start) {
    Node *node = new Node(*start);
    ++count;
    root = meld(root, node);
  }
}

template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>::PairingPQ(COMP_FUNCTOR comp) {
  root = nullptr;
  count = 0; 
  this->compare = comp;
}

template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>::PairingPQ(const PairingPQ& other) {
  count = 0;
  copy(other.root);
}

template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>&
PairingPQ<TYPE, COMP_FUNCTOR>::operator=(const PairingPQ& rhs) {
  queue<Node*> qtemp; 
  if(root != nullptr) {
    destructorfunc(); 
  }
  copy(rhs.root);
  return *this;
}

template<typename TYPE, typename COMP_FUNCTOR>
PairingPQ<TYPE, COMP_FUNCTOR>::~PairingPQ() {
  destructorfunc();
}


template<typename TYPE, typename COMP_FUNCTOR>
void PairingPQ<TYPE, COMP_FUNCTOR>::pop() {
  queue<Node*> qtemp;
  Node *first = nullptr; 
  Node *second = nullptr;

  if(root == nullptr) {
    return; 
  }

  if(root->child == nullptr) {
    delete root;
    root = nullptr;
    --count;
    return; 
  }

  if(root->child != nullptr) {
    first = root->child;
  }

  delete root;
  while(first != nullptr) {
    second = first->sibling;
    first->sibling = nullptr; 
    qtemp.push(first);
    first = second; 
  }
  --count;  
  while(qtemp.size() > 1) {
    first = qtemp.front();
    qtemp.pop();
    second = qtemp.front();
    qtemp.pop();
    root = meld(first, second);
    qtemp.push(root);
  }
  root = qtemp.front();
  qtemp.pop();

}



template<typename TYPE, typename COMP_FUNCTOR>
const TYPE& PairingPQ<TYPE, COMP_FUNCTOR>::top() const {
  return root->elt; 
}

template<typename TYPE, typename COMP_FUNCTOR>
void PairingPQ<TYPE, COMP_FUNCTOR>::push(const TYPE& val) {
  Node *np =  new Node(val); 
  ++count;
  if(root == nullptr) {
    root = np; 
  }
  else {
    root = meld(root, np);
  }
}

#endif //PAIRING_H


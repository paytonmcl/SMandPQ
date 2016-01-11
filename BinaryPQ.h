#ifndef BINARY_H
#define BINARY_H

#include "Eecs281PQ.h"
#include <iostream>

using namespace std; 

//A specialized version of the 'priority_queue' ADT implemented as a binary priority_queue.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
public:
  typedef unsigned size_type;

  //Description: Construct a priority_queue out of an iterator range with an optional
  //             comparison functor.
  //Runtime: O(n) where n is number of elements in range.
  template<typename InputIterator>
  BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR());

  //Description: Construct an empty priority_queue with an optional comparison functor.
  //Runtime: O(1)
  BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR());

  //Description: Add a new element to the priority_queue.
  //Runtime: O(log(n))
  virtual void push(const TYPE& val);

  //Description: Remove the most extreme (defined by 'compare') element from
  //             the priority_queue.
  //Note: We will not run tests on your code that would require it to pop an
  //element when the priority_queue is empty. Though you are welcome to if you are
  //familiar with them, you do not need to use exceptions in this project.
  //Runtime: O(log(n))
  virtual void pop();

  //Description: Return the most extreme (defined by 'compare') element of
  //             the priority_queue.
  //Runtime: O(1)
  virtual const TYPE& top() const;

  //Description: Get the number of elements in the priority_queue.
  //Runtime: O(1)
  virtual size_type size() const
    { return data.size() - 1; }

  //Description: Return true if the priority_queue is empty.
  //Runtime: O(1)
  virtual bool empty() const {
    if(data.size() == 1) {
      return true; 
    }
    return false; 
  }
private:
  //Note: This vector *must* be used your priority_queue implementation.
  std::vector<TYPE> data;
private:
  //***Add any additional member functions or data you require here.
  void swap(int first, int second) {
    TYPE temp = data[first]; 
    data[first] = data[second];
    data[second] = temp;
  }
  void fixUp(int k) {
      while(k > 1 && this->compare(data[k / 2], data[k])) {
        swap(k, k/2);
        k /= 2; 
      }
  }
  void fixDown(int datasize, int k) {
    while(2 * k <= datasize) {
      int j = 2 * k; 
      if(j < datasize && this->compare(data[j], data[j + 1])) {
        j++;
      }
      if(data[j] == data[k] || this->compare(data[j], data[k])) {
        break;
      }
      swap(k, j);
      k = j;
    }
  }
};

template<typename TYPE, typename COMP_FUNCTOR>
template<typename InputIterator>
BinaryPQ<TYPE, COMP_FUNCTOR>::BinaryPQ(
  InputIterator start,
  InputIterator end,
  COMP_FUNCTOR comp
) {
  this->compare = comp;
  data.push_back(*start); 
  for(; start != end; start++) {
    data.push_back(*start);
  }
  for(int i = data.size()/2; i > 0; --i) {
    fixDown(data.size() - 1, i);
  }
}

template<typename TYPE, typename COMP_FUNCTOR>
BinaryPQ<TYPE, COMP_FUNCTOR>::BinaryPQ(COMP_FUNCTOR comp) {
  data.push_back(0);
  this->compare = comp; 
}

template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::push(const TYPE& val) {
  data.push_back(val);
  fixUp(data.size() - 1);
}

template<typename TYPE, typename COMP_FUNCTOR>
void BinaryPQ<TYPE, COMP_FUNCTOR>::pop() {
  if(!empty()) {
    swap(1, data.size() - 1);
    data.pop_back();
    fixDown(data.size() - 1, 1);
  }
}

template<typename TYPE, typename COMP_FUNCTOR>
const TYPE& BinaryPQ<TYPE, COMP_FUNCTOR>::top() const {
  return data[1]; 
}

#endif //BINARY_H


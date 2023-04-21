#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_

#include "utils.h"

template<class T>               // Allows this data structure to use any given type as long as it fits the operations
class ArrayQueue {
    protected:                    // Can only be accessed by 'friend' classes; will see more about this soon 
        // underscores are convention to show that these are member variables
        int _n;                  // number of elements in the queue
        int _j;                  // index j that keeps track of the next element to remove 
        T *_a;                   // backing array
        int _size;               // total size of array, NOT number of elements
        void resize();  

    public:
        // Constructor
        ArrayQueue();

        // Destructor
        ~ArrayQueue();

        //generic remove
        T remove(T x);


        // Add an element, return true
        void enqueue(T x);

        // Remove an element, return an element that got removed
        T dequeue();

        // Empty the stack 
        void clear();
};

//  Constructor and Destructor
//      for the constructor, we initialize a new array as the "backing array"
//      these constructors/destructors can be identical for any array-based implementation
template<class T>
ArrayQueue<T>::ArrayQueue() {
    //won't accept size and set default size as 1
    _a = new T[1];
    _size = 1; 
    _n = 0;
    _j = 0;
}

// default destructor just trashes everything
template<class T>
ArrayQueue<T>::~ArrayQueue() {}


template<class T>
void ArrayQueue<T>::resize() {
    T * b = new T[max(1, 2*_n)];
    for (int i = 0; i < _n; i++) {
        b[i] = _a[i];
    }     
    _a = b;
    _size = max(1, 2*_n);
}

template<class T>
T ArrayQueue<T>::remove(T x){
    int temp = 0;
    for (int i = 0; i < _size+1; i++){
        if(_a[i] == x){
            temp = _a[i];
            
            break;
        }
    }
    return temp;
    
}

// add operation
template<class T>
void ArrayQueue<T>::enqueue(T x) {
    // resize if array is too small to fit 
    if (_n + 1 > _size) {
        resize();
    }

    //insert new element
    _a[(_j+_n)%_size] = x;

    // increase the array element count
    _n++;
}

// remove operation
// book: 2.1.1 
template<class T>
T ArrayQueue<T>::dequeue() {
    // get the original element at the index being removed
    T x = _a[_j];

    _j = (_j+1)%_size;
    // decrease the array element count
    _n--;
    // resize if array is too large for the data 
    if (_size >= 3 * _n) {
        resize();
    }
    // original element in case we want it
    return x;
}

// Clear out the stack 
template<class T>
void ArrayQueue<T>::clear() {
    _n = 0;                    // no more elements 
    _j = 0;
    T *b = new T[1];           // create new, single-element, empty array
    _a = b;                    // overwrite existing array
}

#endif /* ARRAYQUEUE_H */
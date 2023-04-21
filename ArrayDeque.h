#ifndef ARRAYDEQUE_H_
#define ARRAYDEQUE_H_

#include "utils.h"

template<class T>               // Allows this data structure to use any given type as long as it fits the operations
class ArrayDeque {
    protected:                    // Can only be accessed by 'friend' classes; will see more about this soon 
        // underscores are convention to show that these are member variables
        int _n;                  // number of elements in the Deque
        int _j;                  // index j that keeps track of the next element to remove 
        T *_a;                   // backing array
        int _size;               // total size of array, NOT number of elements
        void resize();  

    public:
        // Constructor
        ArrayDeque(int n);

        // Destructor
        ~ArrayDeque();

        T get(int i);
        T get2(T x);
        int get3();
        T set(int i, T x);

        // Add an element, return true
        void add(int i, T x);

        // Remove an element, return an element that got removed
        T remove(int i);
        

        // Empty the stack 
        void clear();
};


template<class T>
ArrayDeque<T>::ArrayDeque(int n) {
    //won't accept size and just set default size as 1
    _a = new T[n];
    _size = n; 
    _n = 0;
    _j = 0;
}

// default destructor just trashes everything
template<class T>
ArrayDeque<T>::~ArrayDeque() {}

template<class T>
T ArrayDeque<T>::get(int i){
    T x = _a[(_j+i)%_size];
    return x;
}

template<class T>
T ArrayDeque<T>::get2(T x){
    int i = 0;
    for (i = 0; i < _size+1; i++){
        if(_a[i] == x){
            break;
        }
    }
    return i;
}

template<class T>
int ArrayDeque<T>::get3(){
    return _n;
}

template<class T>
T ArrayDeque<T>::set(int i, T x){
    T temp = _a[(_j+1)%_size];
    _a[(_j+1)%_size] = x;
    return temp;
}

template<class T>
void ArrayDeque<T>::add(int i, T x) {
    // resize if array is too small to fit 
    if (_n + 1 > _size) {
        resize();
    }

    if (i < _n/2) {
        //front half, so we 땡기는 거
        _j = (_j-1) % _size;
        for(int k=0; k<i; k++){
            _a[(_j+k)%_size] = _a[(_j+k+1)%_size];
        }
    }
    else{
        for(int k=_n; k>_n; k--){
            _a[(_j+k)%_size] = _a[(_j+k-1)%_size];
        }
    }
    _a[(_j+i)%_size] = x;
    _n = _n+1;

    // increase the array element count
    _n++;
}

template<class T>
T ArrayDeque<T>::remove(int i) {
    // get the original element at the index being removed
    T x = _a[(_j+i)%_size];

    if(i< _n/2){
        for(int k=i; k>0; k--){
            _a[(_j+k)%_size] = _a[(_j+k-1)%_size];
        }
        _j = (_j+1)%_size;
    }
    else{
        for(int k=i; k<_n-1; k++){
            _a[(_j+k)%_size] = a[(_j+k+i)%_size];
        }
    }
    --_n;
    // resize if array is too large for the data 
    if (_size >= 3 * _n) {
        resize();
    }
    // original element in case we want it
    return x;
}

// Clear out the deque
template<class T>
void ArrayDeque<T>::clear() {
    _n = 0;                    // no more elements 
    _j = 0;
    T *b = new T[1];           // create new, single-element, empty array
    _a = b;                    // overwrite existing array
}

#endif /* ARRAYDEQUE_H */
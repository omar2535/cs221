`/**
* @file heap.cpp
* Implementation of a heap class.
*/

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2*currentIdx + 1
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2*currentIdx + 2
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    if(currentIdx % 2 ==0){
        return (currentIdx / 2 ) + 1
    }else{
        return (currentIdx / 2) - 1
    }

}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    if(_elems[currentIdx] == NULL){
        return false;
    }
    else{
        return true;
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    int min = _elems[currentIdx];
    if(higherPriority(elems[leftChild(currentIdx)], elems[rightChild(currentIdx)])){
        return leftChild(currentIdx);
    }else{
        return rightChild(currentIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    size_t smallest = maxPriorityChild(currentIdx);
    if(_elems[smallest]> _elems[currentIdx]){
        return;
    }else{
        if(_elems[smallest] < _elems[currentIdx]){
            std::swap(_elems[smallest], _elems[currentIdx]);
            heapifyDown(smallest);
        }
    } 
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.
   
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap

}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    
    return true;
}

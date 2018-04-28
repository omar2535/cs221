#include "stack.h"
#include <vector>
#include "point.h"
using std::vector;


Point Stack::peek(){
    if(size()==0){
        return Point(0,0);
    }else{
        return st.back();
    }   
}

int Stack::size(){
    return st.size();
}

bool Stack::isEmpty(){
    return st.size()==0;
}

void Stack::push(Point p){
    st.push_back(p);
}

Point Stack::pop(){
    Point currentPoint = peek();
    if(size() != 0)
        st.pop_back();
    return currentPoint;
}
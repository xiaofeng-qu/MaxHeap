#include <climits>
// #include <stack>
#include "MaxHeap.hpp"

using namespace std;

template <class U>
void swapD(U &d1, U &d2){
    U temp;
    temp = d1;
    d1 = d2;
    d2 = temp;
}

template <class T>
MaxHeap<T>::MaxHeap(MaxHeap &mh){
    capability = mh.capability;
    last = mh.last;
    data = new T[mh.capability];
    for(int i=0; i<=last; i++){
        data[i] = mh.data[i];
    }
}

template <class T>
void MaxHeap<T>::ascPrintHelper(MaxHeap &mh){
    if(mh.isEmpty()) return;
    T item = mh.removeMax();
    ascPrintHelper(mh);
    std::cout << item;
}

template <class T>
void MaxHeap<T>::insertKey(T d){
    if (isFull()) {
        std::cout << "\nThe heap reaches its capability. Could not insert anymore.\n";
        return;
    }
    ++last;
    data[last] = d;
    int parentId = parent(last), childId = last;
    while(childId != 0 && data[parentId] < data[childId]){
        swapD(data[parentId], data[childId]);
        childId = parentId;
        parentId = parent(childId);
    }
}

template <class T>
void MaxHeap<T>::changeKey(int i, T d){
    data[i] = d;
    int parentId = parent(i), childId = i;
    if(data[parentId] < data[childId]){
        while(childId != 0 && data[parentId] < data[childId]){
            swapD(data[parentId], data[childId]);
            childId = parentId;
            parentId = parent(childId);
        }
    } else {
        MaxHeapify(i);
    }

}

template <class T>
T MaxHeap<T>::deleteKey(int i){
    --last;
    changeKey(i, data[last + 1]);
    return data[i];
}

template <class T>
T MaxHeap<T>::deleteKey(T d){
    T temp = d;
    int i = findKey(d);
    if(i == -1) return temp;
    temp = data[i];
    --last;
    changeKey(i, data[last + 1]);
    return temp;
}

template <class T>
T MaxHeap<T>::removeMax(){
    //if(last == -1) return INT_MIN;
    if(last == 0){
        --last;
        return data[0];
    }
    T root = data[0];
    data[0] = data[last];
    --last;
    MaxHeapify(0);
    return root;
}

template <class T>
T MaxHeap<T>::getMax(){
    return data[0];
}

template <class T>
void MaxHeap<T>::MaxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int largest = i;
    if(l <= last && data[l] > data[i])
        largest = l;
    if(r <= last && data[r] > data[largest])
        largest = r;
    if(largest != i){
        swapD(data[i], data[largest]);
        MaxHeapify(largest);
    }
}

template <class T>
void MaxHeap<T>::descPrint(){
    MaxHeap<T> heapCopy(*this);
    while(!heapCopy.isEmpty()){
        cout << heapCopy.removeMax();
    }
}

template <class T>
void MaxHeap<T>::ascPrint(){
    MaxHeap<T> heapCopy(*this);
    ascPrintHelper(heapCopy);
}
//void MaxHeap<T>::ascPrint(){
//    stack<T> ascStack;
//    MaxHeap<T> heapCopy(*this);
//    while(!heapCopy.isEmpty()){
//        ascStack.push(heapCopy.removeMax());
//    }
//    while(!ascStack.empty()){
//        cout << ascStack.top();
//        ascStack.pop();
//    }
//}

template <class T>
int MaxHeap<T>::findKey(T d){
    for(int i = 0; i <= last; i++){
        if(data[i] == d) return i;
    }
    return -1;
}

template <class T>
void MaxHeap<T>::printData(){
    for(int i = 0; i <= last; i++){
        cout << data[i];
    }
}

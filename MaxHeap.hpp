#ifndef MAXHEAP_HPP_INCLUDED
#define MAXHEAP_HPP_INCLUDED
#include <iostream>
#include <string>

using namespace std;

struct StudentById{
    string firstname;
    string lastname;
    int id;
    float gpa;
    StudentById(){}
    StudentById(string fn, string ln, int id, float gpa){
        firstname = fn;
        lastname = ln;
        this->id = id;
        this->gpa = gpa;
    }
    bool operator==(StudentById r){
        return id == r.id;
    }
    bool operator<(StudentById r){
        return id < r.id;
    }
    bool operator<=(StudentById r){
        return id <= r.id;
    }
    bool operator>(StudentById r){
        return id > r.id;
    }
    bool operator>=(StudentById r){
        return id >= r.id;
    }
    friend ostream &operator<<( ostream &output, const StudentById s){
        output << "First Name: " << s.firstname << "\tLast Name: " << s.lastname << "\tID: " << s.id << "\tGPA: " << s.gpa << endl;
        return output;
    }
};

struct StudentByLastName{
    string firstname;
    string lastname;
    int id;
    float gpa;
    StudentByLastName(){}
    StudentByLastName(string fn, string ln, int id, float gpa){
        firstname = fn;
        lastname = ln;
        this->id = id;
        this->gpa = gpa;
    }
    bool operator==(StudentByLastName r){
        return lastname == r.lastname;
    }
    bool operator<(StudentByLastName r){
        return lastname < r.lastname;
    }
    bool operator<=(StudentByLastName r){
        return lastname <= r.lastname;
    }
    bool operator>(StudentByLastName r){
        return lastname > r.lastname;
    }
    bool operator>=(StudentByLastName r){
        return lastname >= r.lastname;
    }
    friend ostream &operator<<( ostream &output, const StudentByLastName s){
        output << "First Name: " << s.firstname << "\tLast Name: " << s.lastname << "\tID: " << s.id << "\tGPA: " << s.gpa << endl;
        return output;
    }
};

template <class T>
class MaxHeap{
    T *data;
    int capability;
    int last;
    void ascPrintHelper(MaxHeap &);
public:
    MaxHeap(int max_size = 100){
        capability = max_size;
        data = new T[max_size];
        last = -1;
    }
    MaxHeap(MaxHeap &);
    ~MaxHeap(){
        delete[] data;
        data = nullptr;
    }
    void insertKey(T);
    T deleteKey(int);
    T deleteKey(T);
    void printData();
    void changeKey(int, T);
    void MaxHeapify(int);
    void ascPrint();
    void descPrint();
    void clearHeap(){
        last = -1;
    }
    int parent(int i){ return (i-1)/2; }
    int left(int i) { return (2*i+1); }
    int right(int i) { return (2*i+2); }
    int heapSize() { return last + 1; }
    int findKey(T);
    bool isEmpty() { return last == -1; }
    bool isFull() { return ( last + 1 ) == capability; }
    T getMax();
    T removeMax();
};

#endif // MAXHEAP_HPP_INCLUDED

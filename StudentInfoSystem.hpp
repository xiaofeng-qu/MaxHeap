#ifndef STUDENTINFOSYSTEM_HPP_INCLUDED
#define STUDENTINFOSYSTEM_HPP_INCLUDED
#include <limits>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <stack>
#include "MaxHeap.hpp"
#include "MaxHeap.cpp"

using namespace std;

class StudentInfoSystem{
private:
    string filePath;
    MaxHeap<StudentById> StudentHeapById;
    MaxHeap<StudentByLastName> StudentHeapByLastName;
    bool byId;

public:
    StudentInfoSystem();
    void menu();
    void getFilePath();
    void readFile();
    void buildById();
    void buildByLastName();
    void deleteRecord();
    void addRecord();
    void printRecords();
    void saveRecords();
    void loadBinary();
    void orderById(){
        byId = true;
    }
    void orderByLastName(){
        byId = false;
    }
    bool isById(){
        return byId;
    }
};

#endif // STUDENTINFOSYSTEM_HPP_INCLUDED

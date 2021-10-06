#pragma once


#include<system_error>
#include "error_code.h"
#include"Utility.h"
using namespace std;
typedef char Queue_entry;
const int maxqueue = 10; // small value for testing
class Queue {
public:
    Queue( );
    bool empty( ) const;
    Error_code serve( );
    Error_code append(const Queue_entry &item);
    Error_code retrieve(Queue_entry &item) const;
    
protected:
    int count;
    int front, rear;
    Queue_entry entry[maxqueue];
};
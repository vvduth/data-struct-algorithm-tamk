#include<iostream>
#include"Stack.h"
#include<stack>
#include"Queue.h"
#include"extended_queue.h"
#include <cstring>
using namespace std ;

void queue_to_stack (Queue& q, Stack& s);
void stack_to_queue (Stack& s, Queue &q);


void print_queue(Queue q){
    double n ; 
    while(!q.empty()){
        q.retrieve(n);
        cout << n << " " ;
        q.serve();
    }
    cout << endl ;
}

void print_stack (Stack s){
    double n ;
    while (!s.empty()){
        s.top(n);
        cout << n << " " ;
        s.pop() ;
    }
    cout << endl ;
}

double sum_of_stack(Stack s) {
    double sum = 0 ;
    double n ;
    while(!s.empty()){
        s.top(n);
        sum = sum + n ;
        s.pop();
    }
    return sum ;

}
double sum_of_queue(Queue q) {
    double sum = 0 ;
    double n ;
    while(!q.empty()){
        q.retrieve(n);
        sum = sum + n;
        q.serve();
    }
    return sum ;

}
void stack_to_queue (Stack& s, Queue &q){
    double n ;
    Stack temp ;
    while (!s.empty()){
        s.top(n);
        temp.push(n);
        s.pop();
    }
    while (!temp.empty()){
        temp.top(n);
        q.append(n);
        temp.pop();
    }
}

void queue_to_stack (Queue& q, Stack& s) {
    double n ;
    while ( !q.empty()){
        q.retrieve(n);
        s.push(n);
        q.serve();
    }
}

void empty_stack_relative(Stack& s, Stack& s1){
    copy_stack_c(s1,s);
    clear(s);
}
void empty_stack_reverse(Stack& s, Stack& s1) {
    Stack temp ;
    double n ;
    while (!s.empty()){
        s.top(n);
        temp.push(n);
        s.pop();
    }
    copy_stack_c(s1,temp);
}

void reverse_queue_by_stack(Queue& q) {
    Stack temp ;
    double n;
    while(!q.empty()){
        q.retrieve(n);
        temp.push(n);
        q.serve();
    }
    while(!temp.empty()){
        temp.top(n);
        q.append(n);
        temp.pop();
    }

}

void reverse_stack_by_queue(Stack& s){
    Queue temp ;
    double t;
    while(!s.empty()){
        s.top(t);
        temp.append(t);
        s.pop();
    }
    while (!temp.empty()){
        temp.retrieve(t);
        s.push(t);
        temp.serve();
    }
}

bool check_equal(Extended_queue& a, Extended_queue &b) {
    double a_top, b_top ;
    bool res = true;
    if (a.size() != b.size()){
        res = false;
    } else {
        while(!a.empty()){
            a.retrieve(a_top);
            b.retrieve(b_top);
            a.serve();
            b.serve();
            if (a_top != b_top){
                res = false;
                break;
            }

        }
        
        
    }
    return res ;
}

int main( )
/* Post: The program has executed simple arithmetic commands entered by the user.
Uses: The class Stack and functions introduction, instructions, do command,
and get command. */
{
    
    string s ;

    cout << "Enter the string: " ; cin >> s ;
    Extended_queue left;
    Extended_queue right;

    int n = s.length();

    char s_array[n+1];

    strcpy(s_array, s.c_str()); 

    for (int i = 0 ; i < n; i++){
        if(s_array[i] != ':'){
            left.append(s_array[i]);
        } else {
            break;
        }
    }
    int  j = left.size();

    for (int i = j + 1; i < n; i++){
        right.append(s_array[i]);
    }
    
    cout << "Left size: " << left.size() << " right size: " << right.size() << endl ; 
    
    if (right.size() == 0) {
        cout << "N" << endl;
    } else if ( left.size() > right.size()){
        cout << "L" <<endl;
    } else if (left.size() < right.size()) {
        cout << "R" << endl ;
    } else if (left.size() ==  right.size() && !check_equal(left,right) ){
        cout << "D" << endl ;
    } else if (check_equal(left,right)){
        cout << "S";
    }
    

}
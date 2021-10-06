#include<iostream>
#include"Stack.h"
#include<stack>
#include"Queue.h"
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

int main( )
/* Post: The program has executed simple arithmetic commands entered by the user.
Uses: The class Stack and functions introduction, instructions, do command,
and get command. */
{
    double Jan, Apr, Jun, Sep, Nov,profit1 , profit2, lst ;
    Jan = 10 ;
    Apr = 30 ;
    Jun = 20; 
    Sep = 50 ;
    Nov = 30 ;
    Stack s ,s1, s2,s3 ,stockLIFO;
    Queue q, q2, stockFIFO;

    stockLIFO.push(Jan);
    stockLIFO.push(Apr);
    stockLIFO.top(lst);
    stockLIFO.pop();
    profit1 = (Jun - lst) * 100;
    stockLIFO.push(Sep);
    stockLIFO.top(lst);
    stockLIFO.pop();
    profit1 += (Nov - lst) * 100;
    cout << "Profit LIFO is "  << profit1 << " $" <<endl;

    stockFIFO.append(Jan);
    stockFIFO.append(Apr);
    stockFIFO.retrieve(lst);
    stockFIFO.serve();
    profit2 = (Jun - lst) * 100;
    stockFIFO.append(Sep);
    stockFIFO.retrieve(lst);
    stockFIFO.serve();
    profit2 += (Nov - lst)*100;
    cout << "Profit FIFO is "  << profit2 << " $" <<endl;


    
    





    s.push(12);
    s.push(31);
    s.push(122);
    s.push(132);
    s.push(912);
    s.push(1299);
    q2.append(12);
    q2.append(1);
    q2.append(1);
    q2.append(1);
    q2.append(13);
    

    stack_to_queue(s , q);
    print_queue(q);

    queue_to_stack(q,s1);
    print_stack(s1);

    empty_stack_relative(s1,s2);
    print_stack(s2);
    print_stack(s1);

    empty_stack_reverse(s2,s3);
    print_stack(s3);
    print_stack(s2);

    reverse_queue_by_stack(q2);
    print_queue(q2);

    reverse_stack_by_queue(s3);
    print_stack(s3);
  

    

}
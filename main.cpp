#include<iostream>
#include"Stack.h"
#include<stack>
#include"Queue.h"
using namespace std ;


void print_queue(Queue q){
    char n ; 
    while(!q.empty()){
        q.retrieve(n);
        cout << n << " ";
        q.serve();
    }
}


int main( )
/* Post: The program has executed simple arithmetic commands entered by the user.
Uses: The class Stack and functions introduction, instructions, do command,
and get command. */
{
    Queue characs;
    characs.append('a');
    characs.append('e');
    characs.append('f');
    characs.append('a');
    characs.append('r');
    characs.append('a');
    characs.append('1');

    print_queue(characs);

}
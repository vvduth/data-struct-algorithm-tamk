#include <iostream>
#include "Utility.h"
#include "Stack.h"

using namespace std;

bool user_says_yes()
{
	int c;
	bool initial_response = true;

	do {  //  Loop until an appropriate input is received.
		if (initial_response)
			cout << " (y,n)? " << flush;

		else
			cout << "Respond with either y or n: " << flush;

		do { //  Ignore white space.
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');
		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}

Error_code copy_stack_a(Stack& dest, const Stack& source)
{
    dest = source;
    return success;
}

Error_code copy_stack_b(Stack& dest, Stack& source)
{
    Stack temp;
    Stack_entry entry;
    Error_code err;

    
    while (!source.empty())
    {
        
        err = source.top(entry);
        if (err != success)
        {
            return err;
        }

        err = temp.push(entry);
        if (err != success)
        {
            return err;
        }
        err = source.pop();
        if (err != success)
        {
            return err;
        }
    }

    while (!temp.empty())
    {
        err = temp.top(entry);
        if (err != success)
        {
            return err;
        }
        err = source.push(entry);
        if (err != success)
        {
            return err;
        }
        err = dest.push(entry);
        if (err != success)
        {
            return err;
        }
        err = temp.pop();
        if (err != success)
        {
            return err;
        }
    }

    return success;
}

Error_code copy_stack_c(Stack& dest, const Stack& source)
{
    for (int i = 0; i < source.count; i++)
    {
        dest.entry[i] = source.entry[i];
    }
    dest.count = source.count;
    return success;
}

bool full(const Stack& s)
{
    Stack temp = s;

    Stack_entry* newItem = new Stack_entry();
    Error_code err = temp.push(*newItem);

    if (err == success)
    {
        cout << "Stack is not full yet" <<endl ;
        return false;
    }
    else
    {
        cout << "stack is full";
        return true;
    }
}

Error_code pop_top(Stack& s, Stack_entry& t)
{
    Error_code err = s.top(t);
    s.pop();
    return err;
}

void clear(Stack& s)
{
    while (!s.empty())
    {
        s.pop();
    }
    return;
}

int size(const Stack& s)
{
    int count = 0;
    Stack temp = s;
    while (!temp.empty())
    {
        temp.pop();
        count++;
    }
    return count;
}

void delete_all(Stack& s, Stack_entry x)
{
    Stack temp;
    Stack_entry entry;

   

    while (!s.empty())
    {
        s.top(entry);
        if (entry != x)
        {
            temp.push(entry);
        }
        s.pop();
    }

   
    while (!temp.empty())
    {
        temp.top(entry);
        s.push(entry);
        temp.pop();
    }
    return;
}

#pragma once
#include "error_code.h"
#include "Stack.h"


Error_code copy_stack_a(Stack& dest, const Stack& source);
Error_code copy_stack_b(Stack& dest, Stack& source);


bool full(const Stack& s);


Error_code pop_top(Stack& s, Stack_entry& t);


void clear(Stack& s);

int size(const Stack& s);


void delete_all(Stack& s, Stack_entry x);

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <time.h>
#include "Stack.h"
using namespace std;

enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};

bool user_says_yes();

Error_code copy_stack_a(Stack& dest, const Stack& source);
Error_code copy_stack_b(Stack& dest, Stack& source);


bool full(const Stack& s);


Error_code pop_top(Stack& s, Stack_entry& t);


void clear(Stack& s);

int size(const Stack& s);


void delete_all(Stack& s, Stack_entry x);

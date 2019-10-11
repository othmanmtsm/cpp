//header files microsoft docs
#ifndef MY_CLASS_H // include guard
#define MY_CLASS_H
#include "my_class.h" // header in local directory
#include <iostream> // header in standard library

using namespace N;
using namespace std;

void my_class::do_something()
{
    cout << "Doing something!" << endl;
}
#endif
#include <iostream>
using namespace std;

#include "../lib.h"
using namespace lisp;


i16 main() {
    Var<Nil> nil(new Nil());
    Var<List> list_a(new List());
    Var<Value> value = nil.cast<Value>();
    Var<Value> list_b = list_a.unwrap()->push(value);
    return 0;
}

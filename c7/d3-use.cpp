/*
  clang++ -std=c++23 -stdlib=libc++ \
  -fprebuilt-module-path=.modules \
  c7/d3-use.cpp \
  .modules/foo.o .modules/PPP.o .modules/std.o \
  -o c7/d3-use.out
*/

import PPP;
import foo;

using namespace std;
using namespace PPP;

int main()
{
    print_foo();
    set_foo(5);
    print_foo();
    int new_foo = get_foo();
    cout << "new foo: " << new_foo << '\n';
}
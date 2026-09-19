/*
  clang++ -std=c++23 -stdlib=libc++ \
  -fprebuilt-module-path=.modules \
  -x c++-module -c c7/d3-foo.cppm \
  -fmodule-output=.modules/foo.pcm \
  -o .modules/foo.o
*/

export module foo;

import PPP;

using namespace std;
using namespace PPP;

int foo = 0;

export void print_foo()
{
    cout << "foo = " << foo << '\n';
}

export void set_foo(int x)
{
    foo = x;
}

export int get_foo()
{
    return foo;
}

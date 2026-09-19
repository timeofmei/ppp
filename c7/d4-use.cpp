/*
  clang++ -std=c++23 -stdlib=libc++ \
  -IPPP -fprebuilt-module-path=.modules \
  c7/d4-foo.cpp c7/d4-use.cpp \
  .modules/PPP.o \
  -o c7/d4-use.out
*/

#include "d4-foo.h"

int main()
{
    print_foo();
    print(foo);
    print(5);
}

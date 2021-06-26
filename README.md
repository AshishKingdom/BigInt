# BigInt
A C++ Library which allow you to use huge integers and perform basic mathematical operation to it.
**Work in Progress**

# How to Use
1. Compile `BigInt.cpp`. Here I'm using MingW G++
```
g++ -c BigInt.cpp -o BigInt.o
```
2. Include `BigInt.hpp` in your program.
```cpp
#include "BigInt.hpp"

int main()
{
    //your code
}
```

3. To run your program, you must compile your code and then link it with `BigInt.o`.
```
g++ -c your_program.cpp -o your_program.o
```
```
g++ your_program.o BigInt.o -o your_program
```

4. Now, you can run your program. :)
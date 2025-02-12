# myCurses ncurses in C++

This is just a small collection of individual programs. Each program is represented in \*.cpp 
and can be compiled and run with some parameters. The programs are sort of standalone, but 
requires some requirements. C++, gcc, g++ and ncurses are the main libraries. 
The code is optimized for C++ -> specifically C++17. For this reason you will see a lot of 

```C++
auto main(int argc, char\*\* argv) -> int
{
  // do something nobody cares about unless it stops working 

}
```

The instruction for every program are kept in the buttom of each file. 
So if you want to know what to do for example box4color.cpp run in a $shell

```bash
cat box4color.cpp
```

and you get 

```C++
// to compile do: 
// g++ -std=c++17 box4colored.cpp -ltinfo -lmenu -lncurses -panel -o box4color 
// execute : 
// $> ./box4color 30 10 3 6 "github rulez"
```

In order to keep things simple as possible, I did not implement any cmake or other build stuff. 
This makes it an easy way to just getting started XD 

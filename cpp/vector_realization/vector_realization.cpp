#include "myvector.h"
#include <iostream>
#include <string>
using namespace std;

void print_reverse(Vector<string> &vec)
{
    cout << "reverse_iterator: " << endl;
    for(Vector<string>::reverse_iterator it = vec.rbegin();
            it != vec.rend();
            ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
}

void print(Vector<string> &vec)
{
    cout << "iterator: " << endl;
    for(Vector<string>::iterator it = vec.begin();
            it != vec.end();
            ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
}

int main(int argc, const char *argv[])
{
    Vector<string> vec(3, "hello");

    for(Vector<string>::const_iterator it = vec.begin();
        it != vec.end();
        ++it)
    {
        cout << *it << endl;
    }
  cout << endl;

    cout << "size=" << vec.size() << endl;
    cout << "capacity:" << vec.capacity() << endl;
    vec.push_back("foo");
    vec.push_back("bar");

    cout << "size:=" << vec.size() << endl;
    cout << "capacity=" << vec.capacity() << endl;

  print_reverse(vec);
  print(vec);
    return 0;
}

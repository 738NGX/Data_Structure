#include <iostream>
#include "AutoTimer.h"
#include "IntVector.h"

using namespace std;

void TestInsertHead(int num)
{
  Sufe::IntVector vec;
  cout << "Insert " << num << " elements at head" << endl;

  AutoTimer timer;
  for (int i = 0; i < num; i++)
  {
    vec.Insert(0, i);
  }
}

void TestReserveAndInsertHead(int num)
{
  Sufe::IntVector vec;
  cout << "Reserve and insert " << num << " elements at head" << endl;

  AutoTimer timer;
  for (int i = 0; i < num; i++)
  {
    // Calling reserve in loop is bad
    vec.Reserve(vec.Size() + 1);
    vec.Insert(0, i);
  }
}

void TestInsertTail(int num)
{
  Sufe::IntVector vec;
  cout << "Insert " << num << " elements at tail" << endl;

  AutoTimer timer;
  for (int i = 0; i < num; i++)
  {
    vec.Pushback(i);
  }
}

int main(int argc, char *argv[])
{
  int num = 50000;
  if (argc > 1)
  {
    num = atoi(argv[1]);
  }

  // test vector is growing while inserting
  Sufe::IntVector foo;
  cout << "Making foo[] grow:" << endl;
  int cap = foo.Capacity();
  cout << "size/capacity is " << foo.Size() << " / " << cap << endl;
  for (int i = 0; i < num; i++)
  {
    foo.Pushback(i);
    if (cap != foo.Capacity())
    {
      cap = foo.Capacity();
      cout << "size/capacity becomes " << foo.Size() << " / " << cap << endl;
    }
  }
  cout << endl;

  // test insert patterns
  TestInsertTail(num);           // fastest
  TestInsertHead(num);           // slow
  TestReserveAndInsertHead(num); // slower

  return 0;
}

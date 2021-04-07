#include <iostream>
#include "ndarray.h"
#include <vector>

using namespace std;

int main()
{
  ndarray<int> test {3,0,2};
  for (int x : test)
  {
      cout << x << " ";
  }

  return 0;
}

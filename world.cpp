#include<bits/stdc++.h>

using namespace std;
int main(int argc, char const *argv[])
{
   int i;
   cin >> i;
   deque<string> b;
   string a = "hello";
   string a1 = "hello";
   string a2 = "hello";
   string a3 = "hello";
   string a4 = "hello";
   b.push_back(a);
   b.push_back(a1);
   b.push_back(a2);
   b.push_back(a3);
   b.push_back(a4);
   for ( auto c : b )
      cout << c << ' ';
   return 0;
}
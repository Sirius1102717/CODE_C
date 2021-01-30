/*
 * @Author: Freaver
 * @Date: 2021-01-24 22:42:54
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-30 08:42:30
 */
#include<bits/stdc++.h>
using namespace std;

void str(char a[], char b[])
{
   int i = 0;
   char p[20] = {0};
   char t[20] = {0};
   strcpy(p, a);
   strcpy(p, b);
   while ( *(a + i) ) {
      i++;
   }
   int j = 0;
   while ( *(b + j) ) {
      *(a + i + j) = *(b + j);
      j++;
   }
   cout << a << "\n";
}

int main(int argc, char const *argv[])
{
   char a[20] = "hello";
   char b[20] = "world";
   str(a, b);
   cout<<a;
   return 0;
}

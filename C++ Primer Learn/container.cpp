#include<iostream>
#include<string>
#include<list>
using namespace std;
int main(int argc, char const *argv[])
{
    list<string> a = {"Milton", "Shaekspeare", "Austen"};
    auto it1 = a.begin();
    auto it2 = a.rbegin();
    auto it3 = a.cbegin();
    auto it4 = a.crbegin();


    
    return 0;
}


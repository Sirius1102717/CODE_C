/*
 * @Author: Freaver
 * @Date: 2021-01-27 13:40:40
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-27 14:21:01
 */
#include<bits/stdc++.h>
using namespace std;

void print(string s)
{
    int i;
    stack<int> t;
    for (i = 0; i < s.size(); i++) {
        if (s.at(i) == '(')
            t.push(i);
        else {
            if (s.at(i) == ')') {
                cout<<t.top()<<' '<<i<<'\n';
                t.pop();
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    string s;
    cin>>s;
    print(s);
    return 0;
}

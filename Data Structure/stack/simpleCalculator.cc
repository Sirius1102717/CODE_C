/*
 * @Author: Freaver
 * @Date: 2021-01-27 23:31:25
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-29 11:13:15
 */
#include<bits/stdc++.h>
using namespace std;

bool compare(char c, char top)
{
    if ( top == '(' || top == '*' || top == '/' )
        return true;
    else if ( c == '*' || c == '/' )
        return false;
    else
        return true;
}

string init(string infix)
{
    stack<char> signal;
    string postfix;
    for ( auto c : infix ) {
        if ( c >= '0' && c <= '9' ) {
            postfix += c;
            continue;
        } else {
            if ( signal.empty() || signal.top() == '(' ) {
                signal.push(c);
                continue;
            } else {
                if ( c == '(' ) {
                    signal.push(c);
                    continue;
                } else if ( c == ')' ) {
                    while ( signal.top() != '(' ) {
                        postfix += signal.top();
                        signal.pop();
                    }
                    signal.pop();
                    continue;
                } else {
                    while ( compare(c, signal.top()) && (!signal.empty()) ) {
                        if ( signal.top() != '(' ) {
                            postfix += signal.top();
                            signal.pop();
                        } else {
                            break;
                        }
                    }
                    signal.push(c);
                    continue;
                }
            }
        }
    }
    while ( !signal.empty() ) {
        postfix += signal.top();
        signal.pop();
    }
    
    return postfix;
}

float cal(float &fn1, float fn2, char signal)
{
    if ( signal == '+' )
        fn1 += fn2;
    else if ( signal == '-' )
        fn1 -= fn2;
    else if ( signal == '*' )
        fn1 *= fn2;
    else
        fn1 /= fn2;
    return fn1;
}

float process(string postfix)
{
    stack<float> data;
    for ( auto c : postfix ) {
        if ( c >= '0' && c <= '9' )
            data.push(c- '0');
        else {
            float fn2 = data.top();
            data.pop();
            float fn1 = data.top();
            data.pop();
            cal(fn1, fn2, c);
            data.push(fn1);
        }

    }
    return data.top();
}

int main(int argc, char const *argv[])
{
    string infix;
    cin >> infix;
    string postfix = init(infix);
    cout<<postfix;
    cout << process(postfix) << '\n';
    return 0;
}

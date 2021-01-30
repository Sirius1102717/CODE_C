/*
 * @Author: Freaver
 * @Date: 2021-01-27 23:31:25
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-30 17:53:26
 */
#include<bits/stdc++.h>
#include<multiply.h>
#include<subtraction.h>
#include<division.h>
#include<plus.h>
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

vector<string> init(string infix)
{
    stack<char> signal;
    vector<string> postfix;
    string temp;
    for ( auto c : infix ) {
        if ( c >= '0' && c <= '9' ) {
            temp += c;
            continue;
        } else {
            if ( !temp.empty() )
                postfix.push_back(temp);
            temp.clear();
            if ( signal.empty() || signal.top() == '(' ) {
                signal.push(c);
                continue;
            } else {
                if ( c == '(' ) {
                    signal.push(c);
                    continue;
                } else if ( c == ')' ) {
                    while ( signal.top() != '(' ) {
                        temp += signal.top();
                        postfix.push_back(temp);
                        temp.clear();
                        signal.pop();
                    }
                    signal.pop();
                    continue;
                } else {
                    while ( compare(c, signal.top()) ) {
                        if ( signal.top() != '(' ) {
                            temp += signal.top();
                            postfix.push_back(temp);
                            temp.clear();
                            signal.pop();
                            if ( signal.empty() )
                                break;
                        } else {
                            break;
                        }
                    }
                }
                signal.push(c);
                continue;
            }
        }

    }
    while ( !signal.empty() ) {
        temp += signal.top();
        postfix.push_back(temp);
        signal.pop();
        temp.clear();
    }
    return postfix;
}

void cal(char *fn1, char *fn2, string signal)
{
    if ( signal.compare("+") == 0 )
        highPlus(fn1, fn2);
    else if ( signal.compare("-") == 0 )
        highSub(fn1, fn2);
    else if ( signal.compare("*") == 0 )
        highMul(fn1, fn2);
    else
        highDiv(fn1, fn2);
}

string process(vector<string> postfix)
{
    stack<string> data;
    for ( auto c : postfix ) {
        if ( !(c.compare("+") == 0 || c.compare("-") == 0 || c.compare("*") == 0 || c.compare("/") == 0) )
            data.push(c);
        else {
            char *fn2;
            strcpy(fn2, data.top().c_str());
            data.pop();
            char *fn1;
            strcpy(fn1, data.top().c_str());
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
    vector<string> postfix = init(infix);
    // for ( auto s : postfix )
    //     cout << s;
    cout << process(postfix) << '\n';
    return 0;
}
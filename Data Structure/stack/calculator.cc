/*
 * @Author: Freaver
 * @Date: 2021-01-27 23:54:55
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-28 17:41:20
 */
#include<bits/stdc++.h>
using namespace std;

bool compare(char c, char top)
{
    if ( (c == '*' || c == '/') && (top == '+' || top == '-') )
        return true;
    else
        return false;
}

void f(float &as, float n1, char c)
{

    if ( c == '+' )
        as += n1;
    else if ( c == '-' )
        as -= n1;
    else if ( c == '*' )
        as *= n1;
    else
        as /= n1;
}

void cal1(deque<float> &data, char c)
{

    float n1 = data.back();
    data.pop_back();
    float as = data.back();
    data.pop_back();
    f(as, n1, c);
    data.push_back(as);
}

void cal2(deque<float> &data, char c)
{
    float as = data.front();
    data.pop_front();
    float n1 = data.front();
    data.pop_front();
    f(as, n1, c);
    data.push_front(as);
}

float init(char *s)
{
    deque<float> data;
    deque<char> signal;
    for ( int i = 0; i < strlen(s); i++ ) {

        if ( s[i] >= '0' && s[i] <= '9' ) {
            data.push_back(s[i] - '0');
            continue;
        } else if ( s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-' ) {
            if ( signal.empty() )
                signal.push_back(s[i]);
            else if ( compare(s[i], signal.back()) )
                signal.push_back(s[i]);
            else {
                cal1(data, signal.back());
                signal.pop_back();
                signal.push_back(s[i]);
            }
            continue;
        }
    }
    if ( signal.back() == '*' || signal.back() == '/' ) {
        cal1(data, signal.back());
        signal.pop_back();
    }

    while ( !signal.empty() ) {
        cal2(data, signal.front());
        signal.pop_front();
    }
    return data.front();
}

int main(int argc, char const *argv[])
{
    char s[20] = { 0 };
    cin >> s;
    float as = init(s);
    cout << as;
    return 0;
}

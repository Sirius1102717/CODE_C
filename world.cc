#include <bits/stdc++.h>
using namespace std;

int stringToInt(string s)
{
    int length = (int)s.length();
    int answer = 0;
    if (length % 2 == 1) {
        answer = s.at(length - 1);
        length--;
    }

    for (int i = 0; i < length; i += 2) {
        answer += s.at(i);
        answer += ((int)s.at(i + 1)) << 8;
    }

    return (answer < 0) ? -answer : answer;
}

int main(int argc, char const* argv[])
{
    string s = "Freaver";
    cout << stringToInt(s);
    cout << "\n";
    cout << (2 << 8);
    return 0;
}

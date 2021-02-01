/*
 * @Author: Freaver
 * @Date: 2021-02-01 22:13:45
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-02-01 22:57:10
 */
#include<bits/stdc++.h>
#include <climits>
using namespace std;

bool railLoad(int number[], int numberLen, int trackNum)
{
    stack<int> track[trackNum];
    int i, j;
    int minTop = INT_MAX;
    int minTrackNum = 0;
    int stay = 1;
    for ( i = 0; i < numberLen; i++ ) {
        for ( j = 0; j < trackNum; j++ ) {
            if ( minTrackNum == number[i] ) {
                minTrackNum++;
                cout << "move " << number[i] << '\n';
                continue;
            } else if ( minTop == minTrackNum ) {
                track[minTrackNum].pop();
                cout<< "move "<< minTop<<'\n';
                minTrackNum++;
                minTop = track[minTrackNum].top();
            } else {
                if ( track[j].empty() ) {
                    track[j].push(number[i]);
                    if ( number[i] < minTop ) {
                        minTop = number[i];
                        minTrackNum = j;
                    }
                    break;
                } else if ( number[i] < minTop ) {
                    track[j].push(number[i]);
                    minTop = number[i];
                    minTrackNum = j;
                    break;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

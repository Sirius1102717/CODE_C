/*
 * @Author: Freaver
 * @Date: 2021-01-17 13:57:54
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-30 15:26:35
 */

#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>

inline int sizeJudge(char *clSubtrahend, char *crSubtrahend, int len)
{
    int i;
    for ( i = 0; i < len; i++ ) {
        if ( clSubtrahend[i] < crSubtrahend[i] )
            return 0;
        else if ( clSubtrahend[i] > crSubtrahend[i] )
            return 1;
    }
    return 1;
}

inline void sub(char *clSubtrahend, char *crSubtrahend, char *cas, int lenL, int lenR, int maxLen)
{
    int i;
    int lSubtrahend[500] = { 0 };
    int rSubtrahend[500] = { 0 };
    int as[501] = { 0 };
    for ( i = 0; i < lenL; i++ ) {
        lSubtrahend[i] = clSubtrahend[lenL - i - 1] - 48;
    }
    for ( i = 0; i < lenR; i++ ) {
        rSubtrahend[i] = crSubtrahend[lenR - i - 1] - 48;
    }
    for ( i = 0; i < maxLen; i++ ) {
        as[i] = lSubtrahend[i] - rSubtrahend[i] + as[i];
        if ( as[i] < 0 ) {
            as[i] += 10;
            as[i + 1]--;
        }
    }
    for ( i = 0; i < maxLen; i++ ) {
        cas[i] = as[maxLen - i - 1] + 48;
    }
}

inline void highSub(char *clSubtrahend, char *crSubtrahend)
{
    char cas[500] = { 0 };
    int lenL = strlen(clSubtrahend);
    int lenR = strlen(crSubtrahend);

    if ( lenL == lenR ) {
        int j = sizeJudge(clSubtrahend, crSubtrahend, lenL);
        if ( j == 0 ) {
            sub(crSubtrahend, clSubtrahend, cas + 1, lenR, lenL, lenR);
            cas[0] = '-';
        } else {
            sub(clSubtrahend, crSubtrahend, cas, lenL, lenR, lenL);
        }
    } else {
        if ( lenL > lenR ) {
            sub(clSubtrahend, crSubtrahend, cas, lenL, lenR, lenL);
        } else {
            sub(crSubtrahend, clSubtrahend, cas + 1, lenR, lenL, lenR);
            cas[0] = '-';
        }
    }
    strcpy(clSubtrahend, cas);
}
/*
 * @Author: Freaver
 * @Date: 2021-01-16 19:18:27
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-30 15:15:32
 */
#include<stdio.h>
#include<algorithm>
#include<string.h>

void highPlus(char *clAddend, char *crAddend)
{
    char cas[501] = { 0 };
    int lenL = strlen(clAddend);
    int lenR = strlen(crAddend);
    int maxLen = std::max(lenL, lenR);
    int lAddend[500] = { 0 };
    int rAddend[500] = { 0 };
    int as[501] = { 0 };
    int i = 0;
    for ( i = 0; i < lenL; i++ ) {
        lAddend[i] = clAddend[lenL - i - 1] - 48;
    }
    for ( i = 0; i < lenR; i++ ) {
        rAddend[i] = crAddend[lenR - i - 1] - 48;
    }

    for ( i = 0; i <= maxLen; i++ ) {
        as[i] = lAddend[i] + rAddend[i] + as[i];
        if ( as[i] >= 10 ) {
            as[i] %= 10;
            as[i + 1]++;
        }
    }
    if ( as[maxLen] != 0 )
        (maxLen)++;
    for ( i = 0; i < maxLen; i++ ) {
        cas[i] = as[maxLen - i - 1] + 48;
    }
    strcpy(clAddend, cas);
    printf("%s\n", clAddend);
}
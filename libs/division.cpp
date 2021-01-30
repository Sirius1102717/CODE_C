/*
 * @Author: Freaver
 * @Date: 2021-01-17 21:54:10
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-30 15:34:55
 */
/*
 * @Author: Freaver
 * @Date: 2021-01-17 21:54:10
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-17 23:37:53
 */

#include<stdio.h>
#include<string.h>

char *highDiv(char *cDividend, char *cDivisor)
{
    int dividend[100] = {0};
    int divisor[100] = {0};
    int i;
    int lenL = strlen(cDividend);
    int lenR = strlen(cDivisor);
    for (i = 0; i < lenL; i++ )
        dividend[i] = cDividend[i] - 48;
    for (i = 0; i < lenR; i++)
        divisor[i] = cDivisor[i] - 48;
}


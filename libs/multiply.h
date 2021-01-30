#include <cstdlib>
#include<stdio.h>
#include<string.h>

inline void hMul(int *lMultiplier, int *rMultiplier, char *cas, int lenL, int lenR)
{

    int i;
    int j;
    int as[4000] = { 0 };
    int len = lenL + lenR;
    for ( i = 0; i < lenR; i++ ) {
        for ( j = 0; j < lenL; j++ ) {
            as[j + i] += (lMultiplier[j] * rMultiplier[i]);
            if ( as[j + i] >= 10 ) {
                as[i + j + 1] += as[j + i] / 10;
                as[j + i] %= 10;
            }
        }
    }
    if ( as[lenL + lenR - 1] == 0 )
        len--;
    for ( i = 0; i < len; i++ ) {
        cas[i] = as[len - i - 1] + 48;
    }
    // return cas;

}
inline void highMul(char *clMultiplier, char *crMultiplier)
{
    char cas[2000] = { 0 };
    if ( clMultiplier[0] == '0' || crMultiplier[0] == '0' ) {
        cas[0] = '0';
        return;
    }
    int lenL = strlen(clMultiplier);
    int lenR = strlen(crMultiplier);
    int lMultiplier[2000] = { 0 };
    int rMultiplier[2000] = { 0 };
    int i;
    for ( i = 0; i < lenL; i++ ) {
        lMultiplier[i] = clMultiplier[lenL - i - 1] - 48;
    }
    for ( i = 0; i < lenR; i++ ) {
        rMultiplier[i] = crMultiplier[lenR - i - 1] - 48;
    }
    if ( lenL >= lenR ) {
        hMul(lMultiplier, rMultiplier, cas, lenL, lenR);
    } else {
        hMul(rMultiplier, lMultiplier, cas, lenR, lenL);
    }
    // clMultiplier = {0};
    strcpy(clMultiplier, cas);
    // system("pause");
}
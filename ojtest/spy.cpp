#include <stdio.h>
#include <string.h>

int MAX(int a, int b, int c) {
    int max = a;
    if (b > max)
        max = b;
    else if (c > max)
        max = c;
    return max;
}
int main(void) {
    int lenA, lenB, lenC;
    while (scanf("%d%d%d", &lenA, &lenB, &lenC) != EOF) {
        char a[100][20] = {0}, b[100][20] = {0}, c[100][20] = {0};
        char as[100][20] = {0};
        int lenAS = 0;
        int i;
        for (i = 0; i < lenA; i++)
            scanf("%s", a[i]);
        for (i = 0; i < lenB; i++)
            scanf("%s", b[i]);
        for (i = 0; i < lenC; i++)
            scanf("%s", c[i]);
        int length = MAX(lenA, lenB, lenC);
        for (i = 0; i < length; i++) {
            if (strcmp(a[i], b[i]) == 0 && strcmp(b[i], c[i]) != 0) {
                strcpy(as[lenAS], b[i]);
                lenAS++;
            }
        }
        if (lenAS == 0)
            printf("No enemy spy\n");
        else {
            for (i = 0; i < lenAS; i++)
                printf("%s ", as[i]);
            printf("\n");
        }
    }
    return 0;
}

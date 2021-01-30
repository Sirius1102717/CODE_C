/*
 * @Author: Freaver
 * @Date: 2020-12-16 23:05:26
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-09 20:48:46
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strStr(char *haystack, char *needle) {
    if (!(*needle))
        return 0;
    int p = -1;
    int i = 0;
    int j = 0;
    int lena = strlen(haystack);
    int lenb = strlen(needle);
    if (lena == lenb ==1 && *haystack == *needle)
        return 0;
    for (i = 0; i <= lena - lenb; i++) {
        if (*(haystack + i) == *needle) {
            for (j = 0; j < lenb; j++) {
                if (*(haystack + i + j) != *(needle + j))
                    break;
            }
            if (j == lenb) {
                p = i;
                break;
            }
        }
    }
    if (p >= 0)
        return p;
    else
        return -1;
}

int main(int argc, char const *argv[]) {
    // char haystack[20] = {0}, needle[20] = {0};
    char haystack[20] = "mississippi", needle[20] = "issip";
    // scanf("%d%d", haystack, needle);
    int p = strStr(haystack, needle);
    printf("%d", p);
    return 0;
}

#include <stdio.h>
#include <string.h>
int main(void) {
  int a, b, c, i, jg = 0;
  while (scanf("%d%d%d", &a, &b, &c) != EOF) {
    char a1[100][20] = {0}, b1[100][20] = {0}, c1[100][20] = {0};
    for (i = 0; i < a; i++)
      scanf("%s", a1[i]);
    for (i = 0; i < b; i++)
      scanf("%s", b1[i]);
    for (i = 0; i < c; i++)
      scanf("%s", c1[i]);
    for (i = 0; i < b; i++) {
      if (strcmp(a1[i], b1[i]) == 0 && strcmp(b1[i], c1[i]) != 0) {
        printf("%s ", b1[i]);
        jg++;
      }
    }
    if (jg == 0)
      printf("No enemy spy\n");
    else
      printf("\n");
    jg = 0;
  }
}

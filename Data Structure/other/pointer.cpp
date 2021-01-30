/**
 * @Author: Freaver
 * @Date: 2021-01-12 21:06:34
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-15 16:36:34
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	int p1, p2, p3;
	scanf("%d%d%d", &p1, &p2, &p3);
	char s[100] = { 0 };
	scanf("%s", s);
	int i;
	int counter = 0;
	int j;
	int k;
	int asN = 0;
	int _num[100] = { 0 };
	char as[1000] = { 0 };
	for ( i = 0; i < strlen(s); i++ ) {
		if ( s[i] == '-' ) {
			_num[++counter] = i;
			for ( j = _num[counter - 1]; j < _num[counter]; j++ ) {
				as[asN] = s[j];
				asN++;
			}
			if ( p3 == 1 ) {
				for ( k = 0; k < p2; k++ ) {
					if ( p1 == 1 || (p1 == 2 && abs(s[i - 1] - s[i + 1]) >= 40) ) {
						for ( j = i - 1; j < j + s[i + 1] - s[i - 1]; j++ ) {
							as[asN] = (char)(s[j] + 1);
							asN++;
						}
					} else if ( p1 == 2 && ((s[i - 1] >= 'a' && s[i - 1] <= 'z') && (s[i + 1]) >= 'a' && s[i + 1] <= 'z') ) {
						for ( j = i - 1; j < j + s[i + 1] - s[i - 1]; j++ ) {
							as[asN] = (char)(s[j] - 31);
							asN++;
						}
					} else if ( p1 == 3 ) {
						for ( j = 0; j < s[i + 1] - s[i - 1]; j++ ) {
							as[asN] = '*';
							asN++;
						}
					}
				}
			} else if ( p3 == 2 ) {
				for ( j = s[i + 1] - s[i - 1]; j > s[i - 1]; j-- ) {
					if ( p1 == 1 ) {
						for ( k = 0; k < p2; k++ ) {
							as[asN] = s[i] + 1;
							asN++;
						}
					} else if ( p1 == 2 && (s[i] >= 'a' && s[i] <= 'z') ) {
						for ( k = 0; k < p2; k++ ) {
							as[asN] = s[i] - 31;
							asN++;
						}
					} else if ( p1 == 3 ) {
						for ( k = 0; k < p2; k++ ) {
							as[asN] = '*';
							asN++;
						}
					}
				}
			}
		}
		i = j;
	}

	printf("%s", as);

	return 0;
}

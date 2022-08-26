/*
 * @Author: Freaver
 * @Date: 2021-01-27 17:42:26
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-27 17:44:14
 *
 */

unsigned long test(unsigned long n)
{
    if ( n == 0 )
        return 0;
    else
        return n & 1 + test(n >> 1);
}

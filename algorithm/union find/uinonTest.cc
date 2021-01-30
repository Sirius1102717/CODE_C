/*
 * @Author: Freaver
 * @Date: 2021-01-25 15:03:08
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-26 12:42:05
 */


#include <iostream>
using namespace std;
const int N = 10010;


/*
 * 将表示朋友圈的数组初始化，即将所有人的“朋友祖先”都设置为自己的 id ，
 * 于是就有了 n 个不同的朋友圈 
 */
void init(int n, int *f) {
    for(int i = 1; i <= n; i++) {
        f[i] = i;
    }
}

// 得到 id 为 v 的人的“朋友祖先”的 id 
int getFriend(int v, int *f) {  
    if(f[v] == v) {
        return v;
    }
    /*
     * 如果发现“朋友祖先”不是自己，那么他肯定被合并到别的朋友圈里面去了，
     * 那么继续调用这个函数来找这个朋友圈里面的“朋友祖先”，
     * 并且在这个过程中将找到的人都设置为同一个“朋友祖先”（因为都在同一个朋友圈里面） 
     */
    return f[v] = getFriend(f[v], f);
}

// 将两个人所在的两个朋友圈合并为一个朋友圈 
void fmerge(int a, int b, int *f, int *high)
{
    int t1 = getFriend(a, f); // 得到左边的人的“朋友祖先” 
    int t2 = getFriend(b, f); // 得到右边的人的“朋友祖先” 
    // 两个人的“朋友祖先”不一样，合并两个朋友圈 
    if ( t1 != t2 ) {
        // 如果左边的朋友圈的高度大于右边的朋友圈的高度，
        // 那么将右边的朋友圈合并到左边的朋友圈中 
        if ( high[t1] > high[t2] ) {
            f[t2] = t1;
            // 否则就把左边的朋友圈合并到右边的朋友圈中 
        } else {
            f[t1] = t2;
            // 如果当前两个朋友圈的高度相等，那么合并之后的朋友圈高度要加一， 
            if ( high[t1] == high[t2] ) {
                high[t2]++;
            }
        }
    }
}

int main() {
    int n, m, k;
    int f[N];
    int high[N];
    cin >> n >> m >> k;
    int x, y;
    init(n, f);

    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        fmerge(x, y, f, high);
    }

    /*
     * 输出合并之后的数组情况
     */
    for(int i = 1; i <= n; i++) {
        if(i != 1) {
            cout << " ";
        }
        cout << f[i];
    }
    cout << endl;

    for(int i = 0; i < k; i++) {
        cin >> x >> y;
        // 如果两个人的“朋友祖先”不相同，证明他们不在同一个朋友圈内，也就不是朋友
        if(getFriend(x, f) != getFriend(y, f)) {
            cout << "no" << endl; 
        } else {
            cout << "yes" << endl;
        }
    }

    return 0;

} 

/*
 * @Author: Freaver
 * @Date: 2021-01-27 00:04:41
 * @Note: test
 * @Description: For learning
 * @LastEditTime: 2021-01-27 12:13:07
 */
 /*
  * @lc app=leetcode.cn id=587 lang=cpp
  *
  * [587] 安装栅栏
  */

  // @lc code=start
#include<bits/stdc++.h>
using namespace std;
class Solution
{
public:

    bool judge(vector<int> a, vector<int> b, vector<int> c)
    {
        int first = (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
        int second = (a[0] - c[0]) * (a[0] - c[0]) + (a[1] - c[1]) * (a[1] - c[1]);
        int third = (c[0] - b[0]) * (c[0] - b[0]) + (c[1] - b[1]) * (c[1] - b[1]);
        if ( (first * first + second * second) <= third * third ) {
            return true;
        } else {
            return false;
        }
    }

    vector<vector<int>> outerTrees(vector<vector<int>> &points)
    {
        int i;
        for ( i = 0; i < points.size() - 2; i++ ) {
            if ( judge(points[i], points[i + 1], points[i + 2]) )
                points[i + 1].pop_back();
        }

        if ( judge(points[0], points[1], points[points.size() - 1]) )
            points[0].pop_back();
        if ( judge(points[1], points[points.size() - 1], points[points.size() - 2]) )
            points[points.size() - 1].pop_back();
        return points;
    }
};
// @lc code=end
int main(int argc, char const *argv[])
{
    Solution s;
    vector<vector<int>> points;
    int i;
    int x, y;
    for ( i = 0; i < 6; i++ ) {
        cin >> x >> y;
        points[i].push_back(x);
        points[i].push_back(y);
    }

    points = s.outerTrees(points);

    for ( auto a : points ) {
        for ( auto b : a )
            cout << b << " ";
        cout << "\n";
    }

    return 0;
}


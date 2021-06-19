#include <iostream>
#include <vector>


class Solution {
public:
    /*
     * 1.有多个选择。
     * 2.有子问题，来给当前提供选择
     * 3.有base
     * 4.有明确的递推、归方向。。。
     * 经典的dp。。。(毕竟记住了。。咋吹都行)
     */
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // 最左边只能从上到下一条路
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }

        // 最上边只能从左到右一条路
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                //能从上面来，能从左边来。全加一起就是能到这个位置有多少路。
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    /*
     * 还可以缩减dp所用的空间。。
     * 代码更简洁了有木有 23333
     */
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j - 1] + dp[j];
            }
        }
        return dp[n - 1];
    }
};
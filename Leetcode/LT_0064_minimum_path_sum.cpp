#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 经典dp了。
     * 1、从(0,0)开始
     * 2、用子事件来决定当前事件
     * 3、从子事件到当前事件有多个选择
     * 4、递推关系
     */
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        dp[0][0] = grid[0][0];
        // 最上面一行
        for (int j = 1; j < m; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        // 最左边一列 (可以省略，放下面处理，放这里也没事儿)
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        for (int i = 1; i < n; i++) {
            // 这里就可以处理左边一列了。。上面处理过了
            // dp[i][0] = dp[i - 1][0] + grid[i][0];
            for (int j = 1; j < m; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[n - 1][m - 1];

    }

    /*
     * 搞个1维的dp。熟练！！
     */
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> dp(m, 0);
        dp[0] = grid[0][0];
        for (int j = 1; j < m; j++) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        for (int i = 1; i < n; i++) {
            dp[0] += grid[i][0];  // 这里别忘记了。。。。老忘记 哎。。
            for (int j = 1; j < m; j++) {
                dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }
        return dp[m - 1];

    }
};
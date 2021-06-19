#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 跟62类似，多了个路障的归零处理就行了。。。
     * 遇到路障这里的dp就不用处理了。。就是初始化的0。
     */
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        for (int j = 0; j < m; j++) {
            if (grid[0][j]) {
                break;
            }
            dp[0][j] = 1;
        }
        for (int i = 1; i < n; i++) {
            if(!grid[i][0]) {
                dp[i][0] = dp[i - 1][0];
            }
            for (int j = 1; j < m; j++) {
                if (grid[i][j]) {
                    continue;
                }
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[n - 1][m - 1];
    }

    /*
     * 这是省空间的1维dp。。。思路一样。不过就是在遇到路障的时候归零一下。。
     * 上面那个可以跳过。这里不行。因为上面那个只是代表了自己。。
     * 下面这个代表了两向。。同时左和上都要用到。。所以要多处理一步。。
     */
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> dp(m, 0);
        for (int j = 0; j < m; j++) {
            if (grid[0][j]) {
                break;
            }
            dp[j] = 1;
        }
        for (int i = 1; i < n; i++) {
            if (grid[i][0]) {
                dp[0] = 0;
            }
            for (int j = 1; j < m; j++) {
                if (grid[i][j]) {
                    dp[j] = 0; //这就是多处理的那一步。
                }
                else {
                    dp[j] = dp[j - 1] + dp[j];
                }
            }
        }
        return dp[m - 1];
    }
};
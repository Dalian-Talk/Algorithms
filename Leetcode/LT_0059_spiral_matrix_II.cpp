#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 这个跟之前的不一样，这里是n*n的。。所以没那么多一行，一列的问题。直接顺序写就好了。。没啥难度
     *
     * Spiral matrix I 还得处理下 和 左的存在性。。比这个麻烦多了。。2333
     */
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int num = 1;
        int loop = n / 2;
        int l = 0;
        while (l <= loop) {
            //上， 左到右
            for (int i = l; i <= n - 1 - l; i++) {
                res[l][i] = num++;
            }
            //右，上到下
            for (int i = l + 1; i <= n - 1 - l; i++) {
                res[i][n - 1 - l] = num++;
            }
            //下，右到左
            for (int i = n - 2 - l; i >= l; i--) {
                res[n - 1 - l][i] = num++;
            }
            //左，下到上
            for (int i = n - 2 - l; i > l; i--) {
                res[i][l] = num++;
            }
            l++;
        }
        return res;
    }
};
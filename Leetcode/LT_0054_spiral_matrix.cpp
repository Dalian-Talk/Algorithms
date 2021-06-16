#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * n*m的matrix
     * 第0圈。
     * 1、j 从 0 到 m - 1
     * 2、i 从 1 到 n - 1
     * 3、j 从 m - 2 到 0
     * 4、i 从 n - 2 到 1
     *
     * 第1圈
     * 1、j 从 1 到 m - 1 - 1
     * 2、i 从 2 到 n - 1 - 1
     * 3、j 从 m - 2 - 1 到 1
     * 4、i 从 n - 2 - 1 到 2
     */

    /*
     * 不想用答案的。。记不住。。自己写这个记得清楚，就一步一步处理就行
     * 上面的规则没错。但是需要一些特殊处理
     *
     * 1、loop的判定。
     * 本来是用 min(n, m) / 2来弄的。。但是发现不对。。 比如 3 * 3 的是2圈， 3 * 2的因为 2/ 2 = 1也变成两圈。。
     * 所以这里因为多转一次会导致出错，所以改成 (min(n,m) + 1) / 2 - 1 来得到真正的圈数，而不是单纯的直接除以2。
     *
     * 2、最上左到右没问题。最右上到下也没问题。
     * 3、最下右到左有问题，因为如果只有一行 1 2 3 4，他会再从右往左回来一趟。
     * 所以这里需要判定，这一行，不是上面那行。怎么判定？上面那行都是从当前loop开始的。所以判断当前最底这个行 是不是loop就行
     * 4、最左下到上也有问题。比如一列的
     *      1
     *      2
     *      3
     *    会最右上到下算一次，然后最左下到上再算一次。而且是顺时针。那么就要再判定一下。这个最左的 不是我们那个最右的。
     *    最右的是 m - 1 - l。 看他是否于loop想等就行了。
     *
     * 感觉还是自己写的规矩能记得清楚 2333。
     */
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int loop = (min(n, m) + 1) / 2 - 1;
        int l = 0;
        vector<int> res;
        while (l <= loop) {
            // 横 最顶左到右
            for (int j = l; j <= m - 1 - l; j++) {
                res.emplace_back(matrix[l][j]);
            }
            // 竖 最右上到下
            for (int i = l + 1; i <= n - 1 - l; i++) {
                res.emplace_back(matrix[i][m - 1 - l]);
            }
            // 横 最下右到左
            if (n - 1 - l != l) {
                for (int j = m - 2 - l; j >= l; j--) {
                    res.emplace_back(matrix[n - 1 - l][j]);
                }
            }
            if (m - 1 - l != l) {
                // 竖 最左下到上
                for (int i = n - 2 - l; i >= l + 1; i--) {
                    res.emplace_back(matrix[i][l]);
                }
            }
            l++;
        }
        return res;
    }
};
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 先写了一个backtracking(接近brute-force，带剪枝)的方法。果不其然TLE了。。23333毕竟情况太多了。。
     *
     * 就是相当于每一个都有俩选择，一个一个选。。选到cur > res就不选了。然后不断的回溯重来。。就跟找combination sum那个逻辑一样往后找就ok了。。2333
     */
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int res = INT_MAX;
        backtracking(costs, 0, 0, res, 0, 0);
        return res;
    }


private:
    void backtracking(vector<vector<int>>& costs, int idx, int cur, int& res, int left, int right) {
        if (cur > res) {
            return;
        }
        if (idx == costs.size()) {
            res = min(res, cur);
            return;
        }
        if (left < costs.size() / 2) {
            backtracking(costs, idx + 1, cur + costs[idx][0], res, left + 1, right);
        }
        if (right < costs.size() / 2) {
            backtracking(costs, idx + 1, cur + costs[idx][1], res, left, right + 1);
        }

    }


    /*
     * 然后就是牛皮的greedy算法。。
     * 其实这个思路自己在做的时候有想过，当然不是最终正确的思路，而是相关的。
     * 我自己在根据例子手写分配过程答案的时候，就想。如果两个是 [183, 159], [999, 44]。那我肯定第一个选183，第二个选44呀。
     * 否则怎么凑最小呢。。
     * 当时心里的想法只是，他大得多。。就选小的。。而且也想到了去排个序啥的。。哎。。。
     * 但是，就少了这么一步(因为自己不会证明啊。。所以就少了。。。。)
     * 就如果能意识到是根据两个数字差距大小来决定选什么的话。。就好很多了。。很明显差的越大的就选那个小的。
     *
     * 所以最终greedy的逻辑就是。
     *
     * [a0, b0], [a1, b1] ... [an-1, bn-1]
     * 就是排序一下，把a0 b0相差最小的那个 放最前，最大的那个放最后。(字面意义，不是绝对值，比如上面999 44这种，放后面就选44了，一个道理。)
     * 因为如果 a0 - b0 是负数，并切负的很多的话。。相当于a0 比 b0小很多。那么选a0合适。因为选b0的话。。b0可能会大很多很多出去。。这是后面其他的组合无法弥补的。。
     * (反正greedy思想是这样。。。为啥对。。那别人证明是对的。。加上自己做的时候也有类似想法。。23333)
     *
     *
     * 下面就是牛皮的greedy了。。。反正我想不到。。我最多就想到上面那种差一步的境界。。还是不够牛皮
     */


    int twoCitySchedCost(vector<vector<int>>& costs) {
        sort(costs.begin(), costs.end(), [](vector<int>& c1, vector<int>& c2) {
            return (c1[0] - c1[1]) < (c2[0] - c2[1]);
        });
        int res = 0;
        int n = costs.size(); // length is even
        for (int i = 0; i < n / 2; i++) {
            res += costs[i][0] + costs[i + n / 2][1];
        }
        return res;
    }
};
#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 因为有了jump game II的学习后就比较简单了。
     * 每到一个位置。先看当前最远能不能到这里。其实也就是所谓的。。我们碰到0了没。。能不能跨过这个0。
     * 如果可以的话。就用当前的最大步数，看能否更新这个最远到达的位置。。
     *
     * 所以说，就是持续更新能够到达的最远位置，直到最后的终点，只要最终能 >= n - 1 就可以，反之就是中间有某个0把路线卡死了。就过不去了。
     *
     * 看答案也可以倒着来。就是从终点往前不断更新当前能到的终点，看能不能走回起点，一个道理。
     */
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int current_end = nums[0];
        for (int i = 1; i < n; i++) {
            if (i > current_end) {
                return false;
            }
            current_end = max(current_end, i + nums[i]);
        }
        return true;
    }

    /*
     * 再写一个最基础的backtracking方法吧，权当练习了。
     *
     *
     * 果不其然 TLE了。。毕竟选择太多。。太慢了。。
     */

    bool canJump(vector<int>& nums) {
        return backtracking(nums, 0, nums.size());
    }

    bool backtracking(vector<int>& nums, int i, int n) {
        if (i >= n - 1) {
            return true;
        }

        for (int step = 1; step <= nums[i]; step++) {
            if (backtracking(nums, i + step, n)) {
                return true;
            }
        }
        return false;
    }
};
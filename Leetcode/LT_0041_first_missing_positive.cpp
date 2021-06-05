#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    /*
     * 经典的数字找位置题目了。O(n) time + O(1) space
     * 这种条件就是让你经典的放在该放的位置上。。然后做判断。。
     *
     * 所以对于任何一个碰到的数字
     * 满足以下组合后
     * 1、如果它不属于这个位置。 例如 2 1， 2就应该在1的位置上
     * 2、它在这个数组里可以有自己的位置 。 反例如 3 1， 3就没有它自己应有的位置
     * 3、它那个位置上数字不是他自己。 也即是那个位置上数字也是不对的。 例如 2 2
     *
     * 那么就进行交换，且保持原地不动。因为交换过来的数字很有可能也是位置不对的，要继续找下去。
     *
     * 这里可以把3个条件柔和成两个(用绝对值。。23333)
     * 所以没差
     * 就这么多条件全部满足后就可以交换了。。否则就去找下一个。。
     *
     *
     * 这是比较经典的题目了。。可以记一下这种做法。=>>>> 数字放在自己应该放在的位置上。。。
     *
     */
    int firstMissingPositive(vector<int>& nums) {
        int i = 0;
        int n = nums.size();

        while (i < n) {
            if (nums[i] != i + 1 && nums[i] <= n && nums[i] > 0 && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
            else {
                i++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};
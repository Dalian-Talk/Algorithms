#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 3Sum的变种，从找target变成找最接近target的。。逻辑上是一样的。。
     * 其实也就是把普通的拿出所有的 3个数的组合，通过排序缩减了组合数量而已。。 时间复杂度从n^3 -> n^2 + nlogn
     * 做多就熟悉了。233333
     *
     */
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int i = 0;
        int diff = INT_MAX;
        int res;
        while (i < n - 2) {
            int partial = target - nums[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                if (nums[left] + nums[right] == partial) {
                    return target;
                }
                else {
                    if (diff > abs(nums[left] + nums[right] - partial)) {
                        diff = abs(nums[left] + nums[right] - partial);
                        res = nums[i] + nums[left] + nums[right];
                    }
                    if (nums[left] + nums[right] > partial) {
                        right--;
                    }
                    else {
                        left++;
                    }
                }
            }
            while (i < n - 2 && nums[i] == nums[i + 1]) i++;
            i++;
        }
        return res;
    }
};
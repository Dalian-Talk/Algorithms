#include <iostream>
#include <vector>

using namespace std;

// -2 -1 0 0 1 2
class Solution {
public:
    /*
     * 记得排序去重！！！233333。去重才是这个题关键所在！！
     * 3Sum的延伸而已
     *
     */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int i = 0;
        vector<vector<int>> res;
        while (i < n - 3) {
            int sum_3 = target - nums[i];
            int j = i + 1;
            while (j < n - 2) {
                int sum_2 = sum_3 - nums[j];
                int left = j + 1;
                int right = n - 1;
                while (left < right) {
                    while (left < right && nums[left] + nums[right] < sum_2) {
                        left++;
                    }
                    while (left < right && nums[left] + nums[right] > sum_2) {
                        right--;
                    }
                    if (left != right && nums[left] + nums[right] == sum_2) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    }
                }
                while (j < n - 1 && nums[j + 1] == nums[j]) j++;
                j++;
            }
            while (i < n - 1 && nums[i + 1] == nums[i]) i++;
            i++;
        }
        return res;

    }
};
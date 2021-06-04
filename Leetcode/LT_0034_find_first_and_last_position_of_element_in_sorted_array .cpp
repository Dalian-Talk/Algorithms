#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 不难。。就是找到后要处理first 和last这个问题。。。2333不是简单的mid + 1。 mid - 1就能处理的。。可以有多个重复的。。要循环找最左最右的
     *
     *
     * 加一句 sorted好的东西。很多时候可以用binary search 把时间复杂度降到logn级别！！！
     */
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                int l_res = mid;
                int r_res = mid;
                while(l_res >= 0 && nums[l_res] == target) {
                    l_res--;
                }
                while(r_res < n && nums[r_res] == target) {
                    r_res++;
                }
                return {l_res + 1, r_res - 1};
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return {-1, -1};
    }
};
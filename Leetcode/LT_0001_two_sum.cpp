#include <iostream>
#include <vector>
#include <unordered_map>


using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       // Brute force。两两组合看能不能加起来等于target
       for (int i = 0; i < nums.size(); i++) {
           for (int j = i + 1; j < nums.size(); j++) {
               // j = i + 1，不是i，重复了。。
               if (nums[i] + nums[j] == target) {
                   return {i, j};
               }
           }
       }

       return {};
    }

    vector<int> twoSum1(vector<int>& nums, int target) {
        // Hash map。看target - 当前数字能否存在于整个数列中
        // 这种情况就是不需要去挨个比较，只要知道用于补足的另一半在不在就行了。
        /*
           处理 6 = 3 + 3这种相同情况的时候，如果只有一个3，那么在第一次count检测的时候就过滤掉了。
           如果有两个3， 那么在遇到第二个3的时候，已经存了第一个3， 那么就可以通过了。
           这种写法就是刚好可以避免掉这种重复的情况，先查再存。
        */
        unordered_map<int, int> num_exist;
        for (int i = 0; i < nums.size(); i++) {
            if (num_exist.count(target - nums[i])) {
                return {i, num_exist[target - nums[i]]};
            }
            num_exist[nums[i]] = i;
        }
        return {};
    }
};


int main() {
    vector<int> nums{2, 7, 11, 15};
    int target = 22;
    Solution s;
//    vector<int> res = s.twoSum(nums, target);
    vector<int> res = s.twoSum1(nums, target);
    for (auto num: res) {
        cout << num << ' ';
    }
}
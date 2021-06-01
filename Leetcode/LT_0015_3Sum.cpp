#include <iostream>
#include <vector>
#include <unordered_map>


using namespace std;


class Solution {
public:
    /*
     * 错误的做法。。思路是想用map做减法来去除重复的结果。
     * 但是如果本身后续就会有重复的结果例如。 [0,0,0,0,0,0,0]
     * 那么这种处理方法永远有概率放入重复的。。
     * 那么去重的话。。要么用个set，要么就排序后一个一个处理。
     * 两个的区别是
     * 1、用set，就方法1做一个延展就行了。。相当于就是 1 + 2Sum + set去重。
     * 2Sum中我们不用去重是因为我们从左到右走一遍即可。而且找到了就可以返回了。这边是输出所有的结果对。。所以这个处理上不太一样。
     * 2、用排序。排序其实也是2Sum的一个解决方案。 比map或者set慢点而已。但是这里可以去重。相当于省去了set的去重事件(set本身也是要时间的)，
     * 而且排序后，处理2Sum的方法也就变成了 two pointers的遍历了。
     * 排序后的去重就是把 1 + 2Sum中的这个1给去掉重复了。。由于每次处理都是从这个1之后的index开始，所以当我们跳过所有相同的1后，之后的处理就不会再
     * 带上这个1了。也就不存在重复的问题了。
     */

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        unordered_map<int, int> num_count;
        for (auto n : nums) {
            num_count[n]++;
        }
        for (int i = 0; i < nums.size() - 2; i++) {
            num_count[nums[i]]--;
            // Two sum
            int target = 0 - nums[i];
            for (int j = i + 1; j < nums.size(); j++) {
                num_count[nums[j]]--;
                int partial = target - nums[j];
                if (num_count[partial] > 0) {
                    res.push_back({nums[i], nums[j], partial});
                }
                else {
                    num_count[nums[j]]++;
                }

            }
        }
        return res;
    }

    /*
     * 其实整个算法的重点在于去重。。。毕竟逻辑上很简单 1 + 2Sum
     * 从上面的第一个方法也可以分析出来就是用排序不错。那么就来列出情况来。
     * a0 a1 a2 a3 a4 a5
     *
     * 1、不难想到的是，如果a0 == a1 == a2。那我们处理完a0之后，就不用处理a1 a2了。因为排过序了，固定a0后，我们只是用two pointers处理后面的a1 a2 a3 a4
     * 当我们到a1后如果不跳过。那么就会获得与a0重复的结果。。
     * 2、中间部分的处理。假设我们当前找到了 a0 + a1 + a5是一组结果。那么left = 1 right = 5，之后这俩要怎么移动？动多少？
     *      a、不难想象，left右移，right左移
     *      b、一次移动一个还是多个？
     *      如果移动一个。那么假设 a1 == a2, a4 == a5那么我们又找到了一组重复结果。。当然用set可以解决。。那为啥不用方法1呢是吧？
     *      所以移动几个还是要根 a0 a1 a2那种情况类似， 相同的都要移动掉。因为没有必要使用了，会重复。
     * 3、中间部分如果a0 + a1 + a5不是结果，那么就有  > < 两种情况。
     * 很明显，< 了就是left太小了， left右移，反之right左移。
     *
     * 这里也可以用while循环来移动，因为重复的部分不用多次判断。 在方法3中写了while的移动。。
     * 要注意left == right的情况。。毕竟出while循环的条件比这个方法2的条件多了个left == right。。。。(才不会说是被 0 0 0 0这种答案给逮到了。。。) 23333
     *
     */

    vector<vector<int>> threeSum1(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int i = 0;
        int n = nums.size();
        while (i < n) {
            int target = 0 - nums[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                if (nums[left] + nums[right] < target) {
                    left++;
                }
                else if(nums[left] + nums[right] > target) {
                    right--;
                }
                else {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                }
            }
            while (i < n - 1 && nums[i + 1] == nums[i]) i++;
            i++;
        }
        return res;
    }


    vector<vector<int>> threeSum2(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int i = 0;
        int n = nums.size();
        while (i < n) {
            int target = 0 - nums[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                while (left < right && nums[left] + nums[right] < target) {
                    left++;
                }
                while (left < right && nums[left] + nums[right] > target) {
                    right--;
                }
                if (left != right && nums[left] + nums[right] == target) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                }
            }
            while (i < n - 1 && nums[i + 1] == nums[i]) i++;
            i++;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> input{0};
    s.threeSum(input);
}
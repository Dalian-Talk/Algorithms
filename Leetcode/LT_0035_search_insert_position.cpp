#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 难度其实不大。主要是去理解binary search的过程。
     *
     * 首先 由于 mid = (left + right) / 2在计算的时候。永远会偏向left，整数的除法问题。
     * 那么来分析找的过程
     * 1、mid比target要小
     *    left = mid + 1
     *    如果因为这一步导致while循环结束了那么left所在位置就应该是target插入的位置了
     *    否则继续
     * 2、mid比target要大
     *    right = mid - 1
     *    如果因为这一步导致while循环结束了那么right + 1就是target应该插入的位置了
     *    这里就是关键了。right + 1是啥？？
     *    我们的while循环条件是left <= right
     *    所以当right = mid - 1导致出这个循环时。。前一刻肯定是left == right
     *    也包括上面的情况1
     *    所以right + 1 = left
     *  那么最终返回left就行。。
     *
     *  所以从上面总结就是。当找不到这个target时，肯定是在left == right后的下一步找到这个target应该有的位置
     *  那么很显然 left == right >> == mid了
     *  小了动left 大了动right
     *  动了left 集体后移一位。所以返回left
     *  动了right 也是集体后移一位(相对于right)，所以right + 1 = left 也就是答案啦。
     *  。。。感觉写多了就想多了。。！！！！按照上面两个情况分析清楚就行了 2333。下面的那部分感想就当扯犊子了。。23333
     *
     */
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        // if (left == n) {
        //     return n;
        // }
        // else {
        //     return right + 1;
        // }
        return left;
    }
};
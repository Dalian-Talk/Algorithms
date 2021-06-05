#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 被268迷惑了双眼。。。这里说只有一个重复的数字。。但是也没说重复多少次啊。。干。。用总和去做有点呆。。。做不出来的。。
     */
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int t_sum = -n;
        int c_sum = 0;
        for (int i = 0; i < n; i++) {
            c_sum += nums[i];
            t_sum += i + 1;
        }
        return c_sum - t_sum;
    }

    /*
     * 总之 solution里面分析了一波龟兔赛跑。。。就跟链表找环题类似。。俩指针，一个快一个慢。。然后跑起来。。
     * 就很牛皮！！！
     * 总之我想不到！！！
     * 那么就记住呗。。看以后能遇到这种类似的题目不，然后还能想起来。23333
     *
     * 感觉能记住一个数字放自己位置，排序、或者set啥的已经。。很happy了。。23333
     */

    int findDuplicate1(vector<int>& nums) {
        int turtle = nums[0];
        int rabbit = nums[0];
        // int rabbit = nums[nums[nums[0]]];
        // while (turtle != rabbit) {
        //     turtle = nums[turtle];
        //     rabbit = nums[nums[rabbit]];
        // }
        do {
            turtle = nums[turtle];
            rabbit = nums[nums[rabbit]];
        } while (turtle != rabbit);

        turtle = nums[0];
        while (turtle != rabbit) {
            turtle = nums[turtle];
            rabbit = nums[rabbit];
        }
        return rabbit;
    }

    /*
     * 这个就是沿袭了41 268弄了数字位置，也是ok的 O(n)不过换位置了。。
     */

    int findDuplicate2(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        while (i < n) {
            if (nums[i] != i + 1 && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
            else {
                i++;
            }

        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return nums[i];
            }
        }
        return n;
    }
};
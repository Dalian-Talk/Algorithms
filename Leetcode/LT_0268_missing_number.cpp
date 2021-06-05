#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 被上一个 hard题目给迷惑了。。毕竟是similar的。。
     * 这边这个做法也没错。把数字放在应该放的位置上。。。
     * 但是其实应该多读读题。。
     *
     *
     * 这里规定了 n个数 并且都是[0,n]之间的，不重复的。这个条件下
     * 自己举个例子就知道了 如果n = 3 从0 开始到3 是4个数，必然少一个。
     * 那么就应该知道。这n个数中，有且只有一个数会少掉，而且是在固定0 1 2 3 。。。。 n的情况下少掉的。。
     * 那么
     * 用0 + 1 + 2 +。。。 + n 然后 减去已经拥有的n个数。。就可以得到结果了。。。
     *
     * 跟41这个hard题不一样。。毕竟41的条件比较宽泛。这个钉死了。。。
     * emmmm
     * 所以做similar题目就是这个后果
     * 容易不动脑子。。TMD
     */
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        while (i < n) {
            if (nums[i] != n && nums[i] != i) {
                swap(nums[i], nums[nums[i]]);
            }
            else {
                i++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                return i;
            }
        }
        return n;
    }


    // 这个就是用总和来求的了
    int missingNumber1(vector<int>& nums) {
        int n = nums.size();
        int t_sum = n;
        int c_sum = 0;
        for (int i = 0; i < n; i++) {
            t_sum += i;
            c_sum += nums[i];
        }
        return t_sum - c_sum;
    }
};
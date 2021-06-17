#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 有啥算法这个题我倒是。。记不得了。就正常的排个序，然后连接起来就行。
     * 这边的技巧是，用结果res的back，也就是最后一个interval与当前interval进行对比。这样子合并起来很方便。
     * 思路就是：
     * 1、首先按照start_i < start_j, end_i < end_j的逻辑去排序，或者end_j可能不需要动？？反正我觉得也排了会好点。这样子能让原来的区间变成
     * --------------
     *     ------
     *       ----------
     *          ------------
     * 排成这种感觉，那么这个时候合并就很清楚了。如果后一个的start在前一个的[start, end]之间，那么就可以合并。否则就单独放一个。
     * 所以这里的技巧就是，既然有后一个和前一个这个行为，就一直用res的back，最后一个，也就是对当前interval来说的上一个。这样子去修改比较，很方便。
     * 我记得以前自己写的时候是用当前和后面的去比。。然后就各种炸裂。。忘记咋炸裂了。。反正炸裂了。。不愿回想 23333。
     * 下面这么写就很舒服。也符合自己的逻辑。
     *
     */

    /*
     * 看了看之前的有个写法是可以不用排end。。想想也确实不用，，反正都是取max。。没差。
     * 就把下面那个给注释了。。也是对的。
     */
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](vector<int>& i1, vector<int>& i2) {
                 if (i1[0] < i2[0]) {
                     return true;
                 }
//                 if (i1[0] == i2[0]) {
//                     return i1[1] < i2[1];
//                 }
                 return false;
             }
        );
        vector<vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] > res.back()[1]) {
                res.push_back(intervals[i]);
            }
            else {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            }
        }
        return res;

    }

    /*
     * 然后看之前代码，有另一个写法就是。用while。因为从上面的for循环逻辑就是。直到我们找到一个interval的 start比当前的end要大。就把当前back换成新的这个interval(也就是把当前push了进去)
     * 所以上面那个for的部分改成while里面套个while逻辑是一样的。。
     * 就下面这种
     */
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        if(intervals.empty() || intervals[0].empty()) return res;
        int size = intervals.size();
        sort(intervals.begin(), intervals.end(), [](vector<int>& v1, vector<int>& v2){ return v1[0] < v2[0];});
        int i = 0;
        while(i < size){
            vector<int>& cur = intervals[i++];
            //这里用while就是往后找，同时更新当前的end。。直到找到一个start比当前end还大。那就是下一个interval了。把当前的放进去，开始下一个就行了。
            //也是挺巧妙的。。不过上下俩是一样的。。
            while(i < size && intervals[i][0] <= cur[1]){
                cur[1] = max(cur[1], intervals[i][1]);
                i++;
            }
            res.push_back(cur);
        }
        return res;
    }
};
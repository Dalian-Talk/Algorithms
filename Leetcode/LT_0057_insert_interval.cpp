#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 过程不难。不过开始自己脑子短路了。。。
     * 我是想直接找到能跟当前interval合成的部分。。。然后就崩了。。因为很有可能找不到。。。
     * 所以后面瞅了眼以前的。。就赶紧换逻辑了。。改成了
     * 先找new_interval之前的。什么是之前的？？end < new_interval.start的就是之前的
     * 然后到某个停下来后就意味着，当前这个可能要和new_interval合并。
     * 合并逻辑也简单。start取小的。。end取大的。
     * 这里start要动的原因是。我们只把所有end < new_interval.start的给去掉了。但是可以有一个start < new_interval.start的。但是 end >new_interval.start
     * 所以start也要动。
     * 然后end取大的已经习惯了。
     * 终止条件就是。。找到一个start > new_interval.end(注意这里的end已经是中间更新过的end了，不是最初的end，因为我们一直在合并)的就代表他们没交集了。就可以停止了
     * 然后把剩余的塞进去就行了。。。
     * 比较简单。。就是处理逻辑别乱就行
     *
     */
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& new_interval) {
        vector<vector<int>> res;
        int n = intervals.size();
        //第一步找到所有在new_interval之前的
        int i = 0;
        while (i < n && intervals[i][1] < new_interval[0]) {
            res.push_back(intervals[i]);
            i++;
        }
        //第二步开始找到能跟new_interval合并在一起的interval，并合并在一起，然后放进去
        while (i < n && intervals[i][0] <= new_interval[1]) {
            new_interval[0] = min(intervals[i][0], new_interval[0]);
            new_interval[1] = max(intervals[i][1], new_interval[1]);
            i++;
        }
        res.push_back(new_interval);
        //第三步把剩余的再放进去
        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }
        return res;
    }
};
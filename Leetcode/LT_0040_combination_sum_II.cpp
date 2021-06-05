#include <iostream>
#include <vector>


using  namespace std;


class Solution {
public:
    /*
     * 跟 39很像。多了个重复数字、且不允许重复使用。结果还不能有重复的。
     * 限制的原因是
     * 在39 提供的数字都是distinct的，所以只要注意使用顺序，就不会重复
     * 40这里提供的数字就带重复，如果不注意处理还是照着39的顺序来做，就重复了。比如
     * 1 10 1 10   target 11
     * 能得到好多的 1 10组合
     *
     * 所以这里就是很明显，如果前面用过1处理了，下一次这个位置不能再用1了。所谓的这个位置。39那边解释，这边自己记录一下。
     * 我们希望找到的是这样的一组结果
     * [] [] [] []
     * 里头所有数加起来等于target
     * 那么我们就一位一位找，使用所有情况(所以再一次给自己脑子里有个印象了。。backtracking就是穷举法+ 剪枝。。233333)
     * 当我们找到第一位比如放 1
     * [1] [] [] []
     * 那么当从这个地方后续处理完后，我们第一个位置要换，也就是for循环走下一个数了，那么就不能再放1了。否则后续大概率重复。
     * 那么就是经典的用一个排序将原数组排个序，然后循环到下一个要放进去的数字的时候，判断这个数字是不是跟前面的相同就行了。。
     *
     * 然后我写跟前面判断的时候还在那想。。我如果跳过了一堆 1。会不会导致少结果？？
     * 其实不会的。我们只是处理了在这个位置上下次不放1。 至于如果后续有一堆1 比如这样的题目 1 1 1 1 1 1 1 2 3 4 5   target = 5
     * 我们找到
     * [1] [1] [1] [1] [1]
     * 这个情况后，下一次 第一个位置，就没有必要放1了，不会跳过结果的原因是，我们在处理的时候根据 cur 和target的大小比较，已经知道了哪些1可以选，
     * 哪些1不能选。能选几个。 (这里是5个)
     * 所以当少于5个的时候，比如后续有2 3 4可以搭配的时候。我们已经在backtracking中 通过对后续 2 3 4 5这四个位置的控制来得到结果了。 这里对第一个位置做循环和重复判断
     * 只是为了不处理额外的结果。
     *
     * 举个例子就是。拿 1 1 1 1 2 3 4 target = 6来说
     * 我开始以为处理完1后跳过所有1会少情况(不知道自己怎么以为的。。总之就是以为了。。。)。但是实际上根据我们的选择(一个数选或者不选)发现，后续所有的1在之后的1的选择中
     * 只会比第一个1的选择少。有点拗口，其实就是
     * 对于第一个1，后续有3个1可以作选或者不选的行为
     * 但是对于第二个1，只有2个了。
     * 所以这么一看就知道了。当处理第一个1的时候。后续所有1的能处理的情况，都包进去了。所以我们才要跳过然后去重！！
     *
     *
     *
     * 当然可以用一个set存所有的结果来去重。。。但是这样不是呆么。。还是直接排序就行，还省了空间事件。
     * 虽然时间复杂度一样。。但是set毕竟元素是个vector。怎么说实际时间都慢点是吧。
     */
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> combo;
        backtracking(candidates, combo, 0, 0, target);
        return res;

    }

private:
    vector<vector<int>> res;
    void backtracking(vector<int>& candidates, vector<int>& combo, int idx, int cur, int target) {
        if (cur == target) {
            res.push_back(combo);
            return;
        }
        if (cur > target || idx == candidates.size()) {
            return;
        }

        for (int i = idx; i < candidates.size(); i++) {
            // 这里开始写成了!= candidates[idx] 有点呆。。别问我怎么想的。。脑子短路就是这样的。。。
            if (i != idx && candidates[i] == candidates[i - 1]) {
                continue;
            }
            combo.push_back(candidates[i]);
            backtracking(candidates, combo, i + 1, cur + candidates[i], target);
            combo.pop_back();
        }
    }
};
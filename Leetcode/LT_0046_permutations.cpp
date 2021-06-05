#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 也是经典的backtracking了，穷举起来就行。比如 3个数 a0 a1 a2
     * 那就是
     * [] [] []
     * 一个一个找就行了，放一个去下一个就行。
     *
     * 这里的问题是中间的swap。举个例子。 1 2 3
     * 我们可以得到
     * [1] [2] [3]
     * [1] [3] [2]
     * 那么下一次开始我们要弄
     * [2] [1] [3]
     * 那么对于原来1这个位置，我们怎么找到2？
     * 简单，for循环下一步就是2了。。但是1怎么办？放哪里？
     * 如果从循环的2的位置开始往后的话。。1就没了。。
     * 所以这个时候要把2换到1的位置。此时2 就是以前的1，1就是以前的2。然后从这个位置开始一步一步再走下去。。
     *
     * 然后这里就是再有个问题了。。
     * 既然我们把2 这次换到了1，之后是不是得换回来？？为什么要换回来？？ 来看流程
     *
     * [1] [2] [3]
     * 此时原数组为 1 2 3
     * 处理完[3]后。我们把 [2] [3]做了第一次交换得到了
     * [1] [3] [2]
     * 此时原数组为1 3 2
     * (诶？？这么发现我不需要用另一个cur就可以在原数组直接做了啊？？赶紧去改改。。。)
     * 我干。。改完后发现。确实不用再用另一个数组了。。因为这里原数组本来换来换去就能得到排列了。。。23333
     *
     * 那么开始重新写分析感想。。。
     * 第一步得到了
     * [1] [2] [3]
     * 流程是 [1] -> [1] [2] -> [1] [2] [3]
     * 然后得到了结果，走到了头，就退回来。怎么退，根据这个单向流程回溯，那就是回到了[1] [2]。即
     * [1] -> [1] [2] -> [1] [2] [3] -> [1] [2]
     * 下一步就是对这个[2]做改变了。怎么变？
     * 既然是全排列，那么这里之前是2，现在就要换2后面的数字过来然后开始下一次了(就跟我们自己不用代码手写的流程其实是一样的。。毕竟穷举。。)
     * [1] -> [1] [2] -> [1] [2] [3] -> [1] [2] -> [1] [3] -> [1] [3] [2]
     * 那么这样子就得到了[1] [3] [2]
     * 那当我们退回去找下一个的时候。流程就是
     * [1] -> [1] [2] -> [1] [2] [3] -> [1] [2] -> [1] [3] -> [1] [3] [2] -> [1] [3] -> [1] [2]
     * 这边就是关键了。
     * 在之前我们把2 3 换了(其实有4后续还会换4过来的，延伸就懒的写下去了。。太长了。。。)那么这里就需要换回来，才能恢复到上一次的状态，也即是回溯。
     *
     * 这里其实光用脑补就知道。。如果换过去。。回来的时候不换回来恢复到上一次状态。。结局肯定要少一些情况。。。(这个真的是纯脑补。毫无分析。。就是这么感觉的
     * 毕竟不换回去，保证一个完美的回溯状态的话。。中间执行不就乱七八糟的 就炸了么？？？？)
     *
     * 所以这种穷举出(也不能算穷举出，怎么说还是有规律的不是？？)所有结果的问题。。重点就是要保证。代码逻辑能够拿到所有结果而不会漏掉。。那保证所有结果最简单的方式不就是
     * 不管干啥。。都从一个标准起点来进行改变而不是中间的某一个状态。。。这样子得到结果的开始以及中间流程就不依赖于一些改变过的状态。而是完美的标准状态咯。。。就没问题了(大概？？？)
     *
     * 言归正传。假设我们不用代码，自己写全排列怎么写？？
     * 1 2 3 4
     * 1 2 4 3
     * 1 3 2 4 >>>> 这里就是关键了。我们是怎么得到这个1 3 2 4的？？ 我们会把 1 2 4 3 先变回 1 2 3 4。然后把3再提到最前面，，然后开始 1 3 2 4。继续看下去
     * 1 3 4 2
     * 1 4 2 3 >>>> 这个也是关键，我们怎么得到的 1 4 2 3？？ 我们是根据排列规律。。。1 4 下一个就是从剩余最小的开始 也就是2。所以是 1 4 2 3
     *              那么从程序角度，我们怎么得到？
     *              我们从 1 3 4 2 结束后，退回成 1 3 2 4 (交换2 4)，然后因为3处理完了 再退回成 1 2 3 4 (交换2 3)，然后得到 1 4 3 2(交换2 4)
     *              诶？这么发现好像跟我们自己逻辑上产生的顺序不一样？？
     *              测试完发现。。就是不一样的。但是这样子我们发现。无论后面做什么处理。都是会退回到从 1 2 3 4这个初始状态，开始进行各种交换。也就是所谓的
     *              从我们选定了某个index的数的初始状态后，所有后续状态最终都会退回到这个状态然后在进行下一步的变化。。
     *
     * 这个当我们处理到 2 1 3 4的时候。固定了2 后续所有的处理都会回归到2 1 3 4开始的状态。无论是2、 1、 3还是4这4个位置中的任何一个。。
     *
     *
     *
     * (反正写的都是屁话。。。这个题TMD，错过一次然后学会了后。。就成会背了一样。。。就跟记住了。。噢对这里就要这么换。。必须这么换。。。23333)
     * (很烦。。总是感觉领悟不到要点。。这样感觉还是不好。。哎。。。)
     *
     */
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> cur;
        backtracking(nums, cur, 0);
        return res;
    }

private:
    vector<vector<int>> res;
    void backtracking(vector<int>& nums, vector<int>& cur, int idx) {
        if (idx == nums.size()) {
            res.push_back(cur);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            swap(nums[i], nums[idx]);
            cur.push_back(nums[idx]);
            backtracking(nums, cur, idx + 1);
            cur.pop_back();
            swap(nums[i], nums[idx]);
        }
    }


public:
    vector<vector<int>> permute1(vector<int>& nums) {
        backtracking1(nums, 0);
        return res;
    }

private:
    vector<vector<int>> res;
    void backtracking1(vector<int>& nums, int idx) {
        if (idx == nums.size()) {
            res.push_back(nums);
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            swap(nums[i], nums[idx]);
            backtracking1(nums, idx + 1);
            swap(nums[i], nums[idx]);
        }
    }
};
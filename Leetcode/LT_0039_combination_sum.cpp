#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 经典的backtracking了。
     * 一堆数，一次选一个，不够，再继续从4个数中选下去。其实也就是穷举法。只不过就是提前判断无法达成结果就结束。
     * 然后选的时候，为了避免重复结果，选完当前这个数后，下一次就不从之前的数选了。因为在处理之前的数的时候，已经把当前以及下一次的情况都处理过了。
     * 再回去就重复了。。
     *
     * 这刚好就又帮我复习了一波sudoku solver那边的问题。。TMD我非要走回去，搞4向 2向啥的。。最终不是无限循环死掉。。就是走不回去了。。好蠢。。23333
     *
     */
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> combo;
        backtracking(candidates, combo, 0, 0, target);
        return res;
    }

private:
    vector<vector<int>> res;
    void backtracking(vector<int>& candidates, vector<int>& combo, int idx, int cur, int target) {
        if (cur == target) {
            res.push_back(combo);
        }
        if (cur > target || idx == candidates.size()) {
            return;
        }
        for (int i = idx; i < candidates.size(); i++) {
            combo.push_back(candidates[i]);
            backtracking(candidates, combo, i, cur + candidates[i], target);
            combo.pop_back();
        }
    }
};
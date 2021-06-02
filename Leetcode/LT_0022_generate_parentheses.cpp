#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 简单的dfs。开始时少了 left < n / 2这个判断。。导致做的时候generate了好多纯左括号的。。有点呆。。。
     *
     * 用 left+right来判断是否结束
     * 用 left > right 来判断是否有足够多的左括号提供给右括号
     */
    vector<string> generateParenthesis(int n) {
        string cur;
        dfs(n * 2, cur, 0, 0);
        return res;
    }

    void dfs(int n, string& cur, int left, int right) {
        if (left + right == n) {
            res.push_back(cur);
            return;
        }
        else {
            if (left > right) {
                cur.push_back(')');
                dfs(n, cur, left, right + 1);
                cur.pop_back();
            }
            // 这个不能少了。。少了就左括号炸裂了。。
            if (left < n / 2) {
                cur.push_back('(');
                dfs(n, cur, left + 1, right);
                cur.pop_back();
            }
        }
    }

private:
    vector<string> res;
};
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 做了数独后。。这个题感觉比那个要简单？？不过数独好判断点，，这个斜边不好判断呀。。
     * 瞅了眼。。可以用技巧
     * 1、正斜线差相同
     * 2、反斜线和相同
     * 3、这样子就可以用简单的数组来进行该线上有无Q的判断了。
     * 一行一行往上(或者下)放皇后就行了
     *
     * 首先是上面的技巧。
     * 然后就是backtracking中的技巧。
     * 我本来是想用一个vector<vector<char>>去构成整个棋盘，然后有结果了再把这些都变成string然后放到res中。
     * 但是其实后面发现。我们每一步只是在乎某个位置能不能放皇后。至于要不要用个棋盘去放。。没必要。。效果是一样的
     * 可以直接把中间的vector<char> 变成定长的string。然后改变string就行。。
     * 开始没想到。。还想最后再转变一次。好呆。。。
     *
     * 或者可能想不到在每一层单独建立一个变量。。就在开始的时候直接把vector<string>建立好整个棋盘就行。。效果一样的。
     */
    vector<vector<string>> solveNQueens(int n) {
        col.resize(n, false);
        diag.resize(2 * n, false);
        anti_diag.resize(2 * n, false);
        N = n;
        vector<string> cur;
        backtracking(cur, n - 1);
        return res;
    }

private:
    vector<bool> col;
    vector<bool> diag;
    vector<bool> anti_diag;
    vector<vector<string>> res;
    int N;
    void backtracking(vector<string>& cur, int i) {
        if (i == -1) {
            res.emplace_back(cur);
            return;
        }
        string cur_level(N, '.');
        for (int j = 0; j < N; j++) {
            // 列 col[j]
            // 对角斜线， i - j + N - 1
            // 反对角斜线，i + j
            if (!col[j] && !diag[i - j + N - 1] && !anti_diag[i + j]) {
                col[j] = true;
                diag[i - j + N - 1] = true;
                anti_diag[i + j] = true;
                cur_level[j] = 'Q';
                cur.emplace_back(cur_level);
                backtracking(cur, i - 1);
                cur_level[j] = '.';
                cur.pop_back();
                anti_diag[i + j] = false;
                diag[i - j + N - 1] = false;
                col[j] = false;
            }
        }

    }

    /*
     * 下面改成了初始化整个cur。用 vector<string> 代替vector<vector<char>>.
     * 变通。。！！！2333
     */
    vector<vector<string>> solveNQueens(int n) {
        col.resize(n, false);
        diag.resize(2 * n, false);
        anti_diag.resize(2 * n, false);
        N = n;
        vector<string> cur(n, string(n, '.'));
        backtracking(cur, n - 1);
        return res;
    }

private:
    vector<bool> col;
    vector<bool> diag;
    vector<bool> anti_diag;
    vector<vector<string>> res;
    int N;
    void backtracking(vector<string>& cur, int i) {
        if (i == -1) {
            res.emplace_back(cur);
            return;
        }
        // string cur_level(N, '.');
        for (int j = 0; j < N; j++) {
            // 列 col[j]
            // 对角斜线， i - j + N - 1
            // 反对角斜线，i + j
            if (!col[j] && !diag[i - j + N - 1] && !anti_diag[i + j]) {
                col[j] = true;
                diag[i - j + N - 1] = true;
                anti_diag[i + j] = true;
                // cur_level[j] = 'Q';
                cur[i][j] = 'Q';
                // cur.emplace_back(cur_level);
                backtracking(cur, i - 1);
                cur[i][j] = '.';
                // cur_level[j] = '.';
                // cur.pop_back();
                anti_diag[i + j] = false;
                diag[i - j + N - 1] = false;
                col[j] = false;
            }
        }
    }

};
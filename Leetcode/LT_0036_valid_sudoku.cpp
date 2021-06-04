#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


class Solution {
public:
    /*
     * 没啥难度。。就是要想到在遍历过程中每一个数字都直接把它对应的行、列、9格都对比了。。而不是单独跑。
     * 开始想法有点呆。。我还想着怎么单独跑会快点。。。233333
     * 看到了用hash table就回想起来这种一遍跑完就行的办法了。。。23333
     *
     * 当然这样用map和set慢了点。。可以直接用静态的记录。因为反正是9*9的格子。。
     *
     * 这里算9格的时候。把整个数组想成一个 3 * 3的大格子。。那么一个点在哪个格子里就变成了 行 / 3 * 3 + 列 / 3
     *
     * 行 / 3 确定在第几行，因为每行有3个数，所以 / 3
     * 然后再乘 3 来获取在那行第一列的位置
     *
     * 列 / 3 就获取第几列
     * 两个加一起就是在3 * 3 的格子中位置了。
     */
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int, unordered_set<char>> row, col, square;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char cur = board[i][j];
                if (cur < '0' || cur > '9') {
                    continue;
                }
                if (row[i].count(cur) || col[j].count(cur) || square[i / 3 * 3 + j / 3].count(cur)) {
                    return false;
                }
                else {
                    row[i].insert(cur);
                    col[j].insert(cur);
                    square[i / 3 * 3 + j / 3].insert(cur);
                }
            }
        }
        return true;
    }

    /*
     * 这个是静态的。。会稍微快点233333
     */

    bool isValidSudoku1(vector<vector<char>>& board) {
        bool row[9][9] = {false}, col[9][9] = {false}, square[9][9] = {false};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int cur = board[i][j] - '0' - 1;
                if (cur < 0 || cur > 8) {
                    continue;
                }

                int square_idx = i / 3 * 3 + j / 3;
                if (row[i][cur] || col[j][cur] || square[square_idx][cur]) {
                    return false;
                }
                else {
                    row[i][cur] = true;
                    col[j][cur] = true;
                    square[square_idx][cur] = true;
                }
            }
        }
        return true;
    }
};
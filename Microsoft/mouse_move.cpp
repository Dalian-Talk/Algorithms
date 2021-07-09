#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <memory>


using namespace std;

/*
 * 起点在(0,0)，所有格子是白的，朝向北
 * 如果当前格子是白色，则右转90度，当前格子染黑，往前走一步
 * 北 -> 东 -> 南 -> 西 -> 北
 * 如果当前格子是黑色，则左转90度，当前格子染白，往前走一步
 * 北 <- 东 <- 南 <- 西 <- 北
 *
 * 0  1  2  3
 * 北 东 南 西
 *
 * (0, 1) (1, 0), (0, -1), (-1, 0)
 *
 * 白块的map
 * {
 *  北: 东
 * }
 *
 * 黑块的map
 * {
 *  北: 西
 * }
 *
 * */

/*
 * k = 3
 * [BB]
 * [WB]
 */

/*
 * [0, 0]  [1, 0]
 * [0, -1] [1 ,-1]
 *
 *
 * [0, 0]  [0, 1]
 * [1, 0]  [1, 1]
 *
 *
 * [BBB]
 * [BBB]
 * [WBB]
 *
 * [-1 1]  [0, 1]  [1, 1]
 * [-1 0]  [0, 0]  [1, 0]
 * [-1 -1] [0, -1] [1, -1]
 *
 *
 * [0, 0]  [0, 1] [0, 2]
 * []
 */

/*
 * base x,y
 * cur x1,y1
 *
 * y - y1, x1 - x
 */

class Solution{
public:
    vector<vector<int>> dirs {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // 顺序对应走北，走东，走南，走西时坐标的变化。
    set<vector<int>> black;
    int max_x = 0, min_x = 0, max_y = 0, min_y = 0;  // 最终矩阵边界

    void run(int k) {
        int cur_dir = 0;  // 北方
        int cur_x = 0;    // 原点
        int cur_y = 0;    // 原点
        while (k--) {
            if (black.find({cur_x, cur_y}) == black.end()) {
                black.insert({cur_x, cur_y});
                cur_dir = (cur_dir + 1) % 4;
            }
            else {
                black.erase({cur_x, cur_y});
                cur_dir = (cur_dir - 1 + 4) % 4;
            }
            vector<int> next_dir = dirs[cur_dir];
            cur_x += next_dir[0];
            cur_y += next_dir[1];
            update_size(cur_x, cur_y);
        }

        int row = max_y - min_y + 1;
        int col = max_x - min_x + 1;
        vector<vector<char>> grid(row, vector<char>(col, 'W'));
        for (auto point: black) {
            int i = max_y - point[1];  // 生成矩阵中的行， 由Y坐标之差生成
            int j = point[0] - min_x;  // 生成矩阵中的列
            grid[i][j] = 'B';
        }

        for (auto& r: grid) {
            cout << '[';
            for (auto element: r) {
                cout << element;
            }
            cout << ']' << endl;
        }

    }

    void update_size(int x, int y) {
        max_x = max(max_x, x);
        min_x = min(min_x, x);
        max_y = max(max_y, y);
        min_y = min(min_y, y);
    }
};


class Solution1{
public:
    vector<tuple<int, int>> dirs {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // 顺序对应走北，走东，走南，走西时坐标的变化。
    set<vector<int>> black;
    int max_x = 0, min_x = 0, max_y = 0, min_y = 0;  // 最终矩阵边界

    void run(int k) {
        int cur_dir = 0;  // 北方
        int cur_x = 0;    // 原点
        int cur_y = 0;    // 原点
        while (k--) {
            if (black.find({cur_x, cur_y}) == black.end()) {
                black.insert({cur_x, cur_y});
                cur_dir = (cur_dir + 1) % 4;
            }
            else {
                black.erase({cur_x, cur_y});
                cur_dir = (cur_dir - 1 + 4) % 4;
            }
            auto [dx, dy] = dirs[cur_dir];
            cur_x += dx;
            cur_y += dy;
            update_size(cur_x, cur_y);
        }

        int row = max_y - min_y + 1;
        int col = max_x - min_x + 1;
        vector<vector<char>> grid(row, vector<char>(col, 'W'));
        for (auto point: black) {
            int i = max_y - point[1];  // 生成矩阵中的行， 由Y坐标之差生成
            int j = point[0] - min_x;  // 生成矩阵中的列
            grid[i][j] = 'B';
        }

        for (auto& r: grid) {
            cout << '[';
            for (auto element: r) {
                cout << element;
            }
            cout << ']' << endl;
        }

    }

    void update_size(int x, int y) {
        max_x = max(max_x, x);
        min_x = min(min_x, x);
        max_y = max(max_y, y);
        min_y = min(min_y, y);
    }
};



int main() {
    Solution s;
    s.run(10);
}
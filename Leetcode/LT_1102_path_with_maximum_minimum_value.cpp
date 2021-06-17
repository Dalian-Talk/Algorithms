#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Solution {
public:
    /*
     * 自己是不会做的。。然后看了答案的。。记录一下自己的理解把。。。
     *
     * 采用的是greedy思想，也就是，每次从当前path往外走的时候，都尽量选大的那个，这样子，最终能够走到终点的时候，我们也是尽量从大的数字走过去的。
     * 这样就保证最终这个path的结果就是最大的那个最小值所在的路径了。
     *
     * 跟Dijkstra的区别在于。。。Dj是每次都找最小的，因为最小是一个最优子问题，可以做下去。
     * 这边是每次都找最大的。最大的不是最优子问题，只是局部最优，无法拓展到全局。所以是个greedy思想。但是在这里刚好这个题可以用这个思想获取结果。。
     *
     * 上面不是我想到的。。反正就是答案的。。牛皮的一比好么。。
     */

    /*
     * 先按照上面逻辑写了最基本的出来。就是最基本的，从每一个点出发，然后优先把大的拿出来进行处理，直到处理到终点。
     */
    int maximumMinimumPath(vector<vector<int>>& grid) {
        vector<vector<int>> directs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int n = grid.size();
        int m = grid[0].size();
        priority_queue<vector<int>> pq;  //默认大顶堆
        pq.push({grid[0][0], 0, 0});
        grid[0][0] = -1;  //因为所有点都是non-negative的，所以用-1就可以代替visited了。方便点
        int res = INT_MAX;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            res = min(res, cur[0]);
            if (cur[1] == n - 1 && cur[2] == m - 1) {
                return res;
            }
            for (auto& d: directs) {
                int next_i = cur[1] + d[0];
                int next_j = cur[2] + d[1];
                if (next_i < 0 || next_i == n || next_j < 0 || next_j == m || grid[next_i][next_j] == -1) {
                    continue;
                }
                pq.push({grid[next_i][next_j], next_i, next_j});
                grid[next_i][next_j] = -1;
            }
        }
        return - 1;
    }
    /*
     * 下面有一个对上面算法的优化。
     * 时间复杂度不变，但是代码稍微。。高级了点，可以提前结束，让实际运行时间减少点。
     *
     * 原理是：
     * 1、上面的算法下，我们是最终取出来大顶堆的顶，然后看他的坐标是不是终点，然后才结束的。
     * 2、那后果就是，如果最终的终点是0呢？？？，那相当于是会被放在堆的最下面，等整个堆都跑完了。。最后一次pop的时候才能判断到。。
     * 3、所以改进的方法就是，当下一次就是终点的时候，提前判断结束就行，因为到终点了，并且每次都是用能找到的最大的去处理，所以没问题。
     *
     * 需要注意的是，需要加 n m == 1的判断，因为我们是用下一个位置去判断是否到终点。。。所以只有一个点就会炸了。。单独加个判断就行。
     */
    int maximumMinimumPath(vector<vector<int>>& grid) {
        vector<vector<int>> directs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int n = grid.size();
        int m = grid[0].size();
        if (n == 1 && m == 1) return grid[0][0];  //这里这个判断原因下面有
        priority_queue<vector<int>> pq;  //默认大顶堆
        pq.push({grid[0][0], 0, 0});
        grid[0][0] = -1;  //因为所有点都是non-negative的，所以用-1就可以代替visited了。方便点
        int res = INT_MAX;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            res = min(cur[0], res);
            for (auto& d: directs) {
                int next_i = cur[1] + d[0];
                int next_j = cur[2] + d[1];
                if (next_i < 0 || next_i == n || next_j < 0 || next_j == m || grid[next_i][next_j] == -1) {
                    continue;
                }
                if (next_i == n - 1 && next_j == m - 1) {
                    return min(res, grid[next_i][next_j]);
                }
                pq.push({grid[next_i][next_j], next_i, next_j});
                grid[next_i][next_j] = -1;
            }
        }
        return - 1;
    }

    /*
     * 再改进点就是，因为我们每次看到下一个点之后，我们就知道对于下一个点，当前最小值是什么了，我们就希望这个时候可以更新最终的结果。
     * 但是这样是不对的。因为我们看到的下一个点并不一定是在最终的路径上的，他只是这边路径上的最小点。如果直接用这个数字更新全局最终结果，那就出错了。。
     * (实际上自己出错好几次了)
     * 所以在处理的时候改为：
     * 1、从一个点找周围的4个点。
     * 2、找到可以放进pq中的点。
     * 3、放进去的时候直接用min处理一下，因为如果当前是5，下一个是100。。那么100也没用，直接放成5，去记录当前这个点所存储的这条路径上最小的那个数字。
     * 这样子相当于在pq中存了所有路径的点的最小值，然后用一个大顶堆把最大的给拿出来了，也就是拿到了 最大的最小值了。(复杂度是不变的。但是更巧一点，节省运行时间)。
     *
     * 这种情况下，相当于用每一次往里放的数字代替了之前的res。然后因为不管数字大小，都统一到了当前最小的，在比较上也会快点。。。(有点dp的感觉？？？23333)
     * 总之就是让总时间变少了。但是时间复杂度还是不变的。
     */

    int maximumMinimumPath(vector<vector<int>>& grid) {
        vector<vector<int>> directs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int n = grid.size();
        int m = grid[0].size();
        if (n == 1 && m == 1) return grid[0][0];  //这里这个判断原因下面有
        priority_queue<vector<int>> pq;  //默认大顶堆
        pq.push({grid[0][0], 0, 0});
        grid[0][0] = -1;  //因为所有点都是non-negative的，所以用-1就可以代替visited了。方便点

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            for (auto& d: directs) {
                int next_i = cur[1] + d[0];
                int next_j = cur[2] + d[1];
                if (next_i < 0 || next_i == n || next_j < 0 || next_j == m || grid[next_i][next_j] == -1) {
                    continue;
                }
                if (next_i == n - 1 && next_j == m - 1) {
                    return min(cur[0], grid[next_i][next_j]);
                }

                pq.push({min(cur[0], grid[next_i][next_j]), next_i, next_j});
                grid[next_i][next_j] = -1;
            }
        }
        return - 1;
    }

    /*
     * 几个优化的方法可以记住，但是最关键的核心。greedy每次找最大的这个思路要记住。。。其他优化都好说。
     */

    /*
     * 下面有个union find写法。这里思路其实是：
     * 1、我们不在乎最终路径长啥样，要不要多绕几步。
     * 2、我们只在乎找到最大的这个最小的数，然后可以生成这么一条路径连接起点和终点的。
     * 3、所以我们从最大的数那个点开始，然后一步一步往小的找，直到找到这么两个点，让起点和终点可以连成一个union。
     * 4、那么我们就相当于找到了结果。
     * 因为我们是从最大值往下找的。所以当找到那一刻，就是最大的最小值了。
     * 这种很有可能找出的最终路径，不是我们所谓的那种，单纯的路径。可能是这种，举个例子
     *
     * 3 3 3 3
     * 3 2 3 3
     * 3 3 2 3
     * 看这种。所有的3都被选上了，但是这不影响最终有这么一条路连接起点和终点，并且最大是3。
     *
     * 所以这么一看就知道了。核心就是从大到小找，不在乎找到的点是不是在那{条}路径上。用条的意思是，宽度为1的这种单向过去的路径，也就是一条过去(不好描述，用心感受23333)
     * 只要找到了那就是ok的。。
     *
     * (说这么多。。反正想不到。。也是别人答案的。。真滴牛皮。但是可以练习一下Union find)
     *
     *
     */
    /*
     * 好久不写Union Find都不会写了。。。。我干。。
     * 首先把Union Find那边注释重新读一遍。。。
     */
    int maximumMinimumPath(vector<vector<int>>& grid) {
        vector<vector<int>> directs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<int>> cells;
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cells.push_back({grid[i][j], i, j});
            }
        }
        sort(cells.begin(), cells.end(), [](vector<int>& a, vector<int>& b) {return a[0] > b[0];});

        UnionFind uf(n * m);
        for (auto& cell: cells) {
            int cur_i = cell[1];
            int cur_j = cell[2];
            grid[cur_i][cur_j] = -1;
            for (auto& d: directs) {
                int next_i = cur_i + d[0];
                int next_j = cur_j + d[1];
                if (next_i >= 0 && next_j >= 0 && next_i < n && next_j < m && grid[next_i][next_j] == -1) {
                    uf.Union(cur_i * m + cur_j, next_i * m + next_j);
                }
                if (uf.find(0) == uf.find(n * m - 1)) {
                    return cell[0];
                }
            }
        }
        return -1;
    }
private:
    class UnionFind {
    public:
        /*
         * 我们需要一个parent：记录某个坐标的parent是谁，这样子，有相同parent的坐标就属于一个集合
         * 我们需要一个find：查找某个坐标的parent，因为过程中存在a的父亲是b，b的父亲是c， c的父亲是c这种逻辑
         * 也就是说，只有找到父亲是自己的那个坐标，才确认到ok，这个坐标才是我们真正需要的该集合的最终parent。
         * 所以在find的过程中，需要用递归的形式去更新parent，从而让整个集合内的坐标点都拥有相同的parent。find同时update。
         *
         * 我们需要一个Union：当两个坐标点可以合并的时候，我们需要把这俩合并在一起。需要：
         * 1、判断这俩坐标点的最终parent是不是一样，一样就不用更新了。
         * 2、如果这俩坐标点最终父亲不一样，那么我们让其中一个的父亲的父亲是另一个父亲就行。举个例子就是
         * 假设现在俩集合
         * 1 2 3 -> 3
         * 4 5 6 -> 6
         * 然后我们通过某个规则发现，2 4可以合在一起了。那么我们拿出2 4的最终parent。一个是3，一个是6。
         * 如何让这俩合在一起？？
         * Union的规矩就是一个Union中所有坐标拥有同一个最终的父亲。
         * 那么简单，就让3的父亲变成6，也就是
         * 1 2 -> 3 -> 6
         * 4 5 6 -> 6
         * 这样子下次更新的时候就会把1 2 都更新到最终父亲是6。
         *
         * 我开始写成了
         * parent[a] = parent[b]。。。我也不知道为啥。。可能好久没写了吧。。UF都不懂了。。这个只是把当前参与合并的点的父亲变成了那边的父亲而已。
         * 我们只动了这一个点，如果这个点运气好最终父亲是自己还行。。如果不是。。那就炸了。。
         * 所以应该是
         * parent[pa] = pb
         * 也就是让集合一的最终父亲的父亲指向集合二的最终父亲，从而合并俩集合。(emm Union Find就这样的。。只能说多理解记忆了。。)
         */
        vector<int> parent;
        UnionFind(int size) {
            parent.resize(size, -1);
        }

        int find(int child) {
            if (parent[child] == - 1) {
                parent[child] = child;
            }
            return parent[child] == child? parent[child]: parent[child] = find(parent[child]);
        }

        void Union(int a, int b) {
            int pa = find(a);
            int pb = find(b);
            if (pa == pb) {
                return;
            }
            parent[pa] = pb;
        }
    };
};
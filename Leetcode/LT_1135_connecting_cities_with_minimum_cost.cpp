#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    // 首先，为啥这个题能想到最小生成树这个算法，看下面网站里的应用，就描述了什么情况下最小生成树很有用
    // https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E7%94%9F%E6%88%90%E6%A0%91/5223845?fr=aladdin

    // 算法的一些教程解释啥的下面。。
    // 经典greedy
    // Kruskal’s Minimum Spanning Tree Algorithm
    // https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

    /*
     * 由于题目明确表达了，如果无法找到这么一条path让所有城市都连接起来的话，那么就返回-1
     * 那么如何才知道找不到这样一条path呢？？
     * 1、我们有n个点，那么要把这n个点最终串在一起的话，需要n-1条边。
     * 2、所以也就是说，如果我们无法通过算法的Union部分让最终边的数量达到n - 1。那么就证明现有的connections无法让所有的点连在一起。也就是返回-1了。
     *
     * 这个行为可以在UF外面做，如果把Find提前在外判断的话
     * 也可以在UF里面做，如果修改Union。从void 到bool把外面的Find行为放到里面的话，也一样的。
     *
     * 之所以要做Find判断，原因是，如果我们找到一条边后，发现这条边的两个点已经有相同的父亲了，这意味着什么？？
     * 根据Union Find的行为，如果两个点有相同的父亲，证明他们已经通过某些其他边连在了一起。类似于
     * a ..... b
     * 然后现在又用一条别的边，如果不进行判断就加进去的话。相当于是 这样
     * a ..... b
     *   XXXXX
     * 这就搞了个环。从算法意义上，不满足最小生成树，从现实意义上，浪费资源。。无法达到最小的cost这个需求。
     *
     * 所以这层判断这边可以记住，用UF可以判断是否有环，也很方便啊！！！
     *
     * 然后就是重要的greedy行为了。每次都选最小的边，然后加上UnionFind的帮忙，就能让我们永远用最小的边去连接所有的点。那么当我们连接到所有点后，就是用最小的总权值了。
     *
     */
    int minimumCost(int n, vector<vector<int>>& connections) {
        sort(connections.begin(), connections.end(), [](vector<int>& c1, vector<int>& c2) {return c1[2] < c2[2];});
        UnionFind uf(n + 1);

        int sum = 0;
        int edge_num = 0;
        for (auto& edge: connections) {
            // 这里可以修改Union，因为Union中做了两个Find以及parent判断。
            // 但是我为了。。练习Union Find的模板。。多熟悉一下，我这里就没改了。。改了也没差一样的道理。
            if (uf.Find(edge[0]) != uf.Find(edge[1])) {
                //如果一个边可以把两个点union到一起，也就是所谓的连在一起，那么最终集合可以有这条边
                //那么就要把现在合法的边数量 + 1
                //最后判断合法的边够不够n - 1来判断这个图能否有把n个点连在一起的一个MST。
                uf.Union(edge[0], edge[1]);
                sum += edge[2];
                edge_num++;
            }
        }
//        return uf.edge == n - 1? sum: -1;
        return edge_num == n - 1? sum: -1;
    }
private:
    class UnionFind {
    public:
        vector<int> parent;
        int edge;
        UnionFind(int size): edge(0) {
            parent.resize(size, -1);
        }

        int Find(int child) {
            if (parent[child] == - 1) {
                parent[child] = child;
            }
            return parent[child] == child? parent[child]: parent[child] = Find(parent[child]);
        }

        void Union(int c1, int c2) {
            int p1 = Find(c1);
            int p2 = Find(c2);
            if (p1 != p2) {
                parent[p1] = p2;
                edge++;
            }
        }
    };
};
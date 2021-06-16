#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * 经典的top K题目。。多了个map
     * 题目要求按id顺序输出。所以如果unordered_map就得sort一遍结果。
     * 如果是map的话。map是红黑树，自带key排序，所以不用担心。
     */
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        map<int, priority_queue<int, vector<int>, greater<>>> map;
//        unordered_map<int, priority_queue<int, vector<int>, greater<>>> map;
        for (auto& item: items) {
            map[item[0]].emplace(item[1]);
            if (map[item[0]].size() > 5) {
                map[item[0]].pop();
            }
        }
        vector<vector<int>> res;
        for (auto& each: map) {
            int total = 0;
            while (!each.second.empty()) {
                total += each.second.top();
                each.second.pop();
            }
            res.push_back({each.first, total / 5});
        }
        // sort(res.begin(), res.end());
        return res;
    }
};
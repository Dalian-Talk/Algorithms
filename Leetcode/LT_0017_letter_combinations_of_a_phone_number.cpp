#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    /*
     * 难度不大，就是一个简单的 dfs或者bfs都行。。 dfs省点空间。。。(如果不算递归栈的话，大概。。哈哈)
     * 要么用empty处理digist是空串
     * 要么在dfs的时候多加一个判断 !cur.empty()
     * 否则会把一个空串push_back到res中。
     */
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        len = digits.length();
        string cur;
        dfs(0, cur, digits);
        return res;
    }

    void dfs(int idx, string& cur, string& digits) {
        if (idx == len) {
            res.push_back(cur);
        }
        else {
            for (auto each: n_to_c[digits[idx]]) {
                cur.push_back(each);
                dfs(idx + 1, cur, digits);
                cur.pop_back();
            }
        }
    }
private:
    int len;
    vector<string> res;
    unordered_map<char, vector<char>> n_to_c{
            {'2', {'a', 'b', 'c'}},
            {'3', {'d', 'e', 'f'}},
            {'4', {'g', 'h', 'i'}},
            {'5', {'j', 'k', 'l'}},
            {'6', {'m', 'n', 'o'}},
            {'7', {'p', 'q', 'r', 's'}},
            {'8', {'t', 'u', 'v'}},
            {'9', {'w', 'x', 'y', 'z'}}
    };
};
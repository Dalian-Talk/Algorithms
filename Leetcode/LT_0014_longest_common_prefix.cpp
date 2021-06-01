#include <iostream>

using namespace std;


/*
 * 比较简单的题。。一个一个比下去就行了。。反正是common prefix。。都得符合。
 * 开始还想着trie树。。后来觉得好像没啥必要。。反正每个字符串都得走一遍。一个一个用当前最长的common prefix比下去就行了。。
 */


class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int size = strs.size();
        string res = strs[0];
        for (int i = 1; i < size; i++) {
            int j = 0;
            while (j < res.length() && j < strs[i].length()) {
                if (res[j] == strs[i][j]) {
                    j++;
                }
                else {
                    break;
                }
            }
            res = res.substr(0, j);
        }
        return res;
    }
};
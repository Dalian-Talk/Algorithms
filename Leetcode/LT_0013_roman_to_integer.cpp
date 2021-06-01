#include <iostream>
#include <unordered_map>

using namespace std;

/*
 * 很简单的处理。。咋都行。。
 */

class Solution {
private:
    unordered_map<char, pair<int, int>> c_to_n{
            {'I', {1, 0}},
            {'V', {5, 1}},
            {'X', {10, 2}},
            {'L', {50, 3}},
            {'C', {100, 4}},
            {'D', {500, 5}},
            {'M', {1000, 6}}
    };
public:
    int romanToInt(string s) {
        int length = s.length();
        int res = 0;
        int i = 0;
        while (i < length) {
            if (i + 1 < length && c_to_n[s[i + 1]].second > c_to_n[s[i]].second) {
                res += c_to_n[s[i + 1]].first - c_to_n[s[i]].first;
                i += 2;
            }
            else {
                res += c_to_n[s[i]].first;
                i += 1;
            }
        }
        return res;
    }
};
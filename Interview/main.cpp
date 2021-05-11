#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
// 0 1 2 3 4
// a b c a b c a b c a
// k = 4
// a b c
// a b c d e
// a b a


int find_k_distinct_characters_substring(string& s, int k) {
    // 直观的做法，两个pointer一个一个往后找
    unordered_map<char, int> count;
    unordered_set<string> res;
    int left = 0, right = 0;
    int length = s.length();

    while (right < length) {
        while (right < length && right - left < k && count[s[right]] < 1) {
            count[s[right++]]++;
        }

        if (right - left == k) {
            res.insert(s.substr(left, k));
        }
        count[s[left++]]--;
        while (left < right && count[s[left]] > 1) {
            count[s[left++]]--;
        }

    }
    return res.size();
}

// k = 3
// a b c d a b c a b c




int find_k_distinct_characters_substring_1(string& s, int k) {
    // 用map的方法，快速跳跃
    unordered_map<char, int> m;
    unordered_set<string> res;
    int left = 0, right = 0;
    int length = s.length();
    while (left < right) {
        char cur = s[right];
    }

}





int main() {
    string s = "abcdabcabc";
    int k = 3;
    cout << find_k_distinct_characters_substring(s, k);
}
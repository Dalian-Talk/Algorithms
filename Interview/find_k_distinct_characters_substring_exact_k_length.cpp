#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 这个代码还可以改进改进更好看。。


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

// k = 5
// b c a d a b c a b c
// l   l l r



int find_k_distinct_characters_substring_1(string& s, int k) {
    unordered_map<char, int> m;
    unordered_set<string> res;
    int left = 0, right = 0;
    int length = s.length();
    while (right < length) {
        char cur = s[right];
        if (m[cur] == 0) {
            m[cur]++;
            k--;
        }
        else {
            while (left < right && s[left] != cur) {
                m[s[left]]--;
                left++;
                k++;
            }
            left++;
        }
        if (k == 0) {
            res.insert(s.substr(left, right - left + 1));
            m[s[left]]--;
            left++;
            k++;
        }
        right++;
    }
    return res.size();

}


// Geek做法，直接用一个k的window来做。 类似于median of two arrays，因为固定长，有个windows更方便，median固定一般长一个道理。
int find_k_distinct_characters_substring_2(string& s, int k) {
    unordered_set<char> contain;
    unordered_set<string> res;

    // 找到一个 (k - 1) 的window
    for (int i = 0; i < k - 1; i++) {
        contain.insert(s[i]);
    }

    // 从第k个字母开始
    for (int i = k - 1; i < s.length(); i++) {
        contain.insert(s[i]);
        if (contain.size() == k) {
            res.insert(s.substr(i + 1 - k, k));
        }
        contain.erase(s[i + 1 - k]);
    }
    return res.size();
}




int main() {
    string s = "abcdabcabc";
    int k = 3;
    cout << find_k_distinct_characters_substring(s, k) << endl;
    cout << find_k_distinct_characters_substring_1(s, k) << endl;
    cout << find_k_distinct_characters_substring_2(s, k) << endl;
}
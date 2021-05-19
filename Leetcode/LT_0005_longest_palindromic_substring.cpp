#include <iostream>

using namespace std;

// Brute-force方法就是把所有的字符串找出来，然后一个一个看是不是回文的
// DP的方法出现是因为，回文的特点，如果 A1A2.....B2B1 是回文， 那么 A2.....B2也必然是回文。
// 所以这是一个子事件，我们找到一个 A2...B2这样的字符串就可以继续两边找下去。而不需要单独扩展单边。 属于浪费
// 再有一个节省时间的点就是
// aaa这种连续相同的字符，没有必要一次次次移动。 因为 相同的必然回文，不论奇数 aaa还是偶数 aaaa都一定是回文。
// 这个也是一个快速移动index到下一次该处理的地方的一个小技巧了


// 反正。。怎么说呢。。这个题。。记住了。。233333
class Solution {
public:
    string longestPalindrome(string& s) {
        int length = s.length();

        int i = 0;
        string res;
        while (i < length) {
            int left = i;
//            int right = i; // 正常是要从这里就开始记录right， 因为从这个i开始两边往外扩展，去看有没有回文。
                             // 但是上面说了加速的问题，我们可以快速跳过相同的部分，不需要额外冗余处理以至于浪费时
            while (i < length - 1 && s[i] == s[i + 1]) {
                //因为我们希望停到跟left对应字符一样的地方。所以选择i == i + 1 而不是i - 1 == i
                i++;
            }
            int right = i; //这就是最后一个与left相同的地方了
            i++; // i去下一次的开始点就行了

            while (left > 0 && right < length && s[left] == s[right]) {
                // 这里left >= 0。。。老写错成 >0 。。就是left能取到正常字符的条件。。。咋就反应不过来呢。。2333
                // 简单的往两边走就是了
                left--;
                right++;
            }
            if (right - left - 1 >= res.length()) {
                res = s.substr(left + 1, right - left - 1);
            }
        }
        return res;
    }
};


int main() {
    return 0;
}
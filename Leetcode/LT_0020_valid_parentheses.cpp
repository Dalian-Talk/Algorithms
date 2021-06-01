#include <iostream>
#include <stack>

using namespace std;


class Solution {
public:
    /*
     * 真的就以前犯什么错。现在还是犯什么错。。诶西。。
     *
     * 1、忽略了只有 右括号的情况。。。判断炸了
     * 2、忽略了处理到中间，，只有右括号的情况。。。判断炸了。
     * 3、忽略了只有左括号的问题。。。结果炸了。。
     * ！！！！！TMD好气。。
     */
    bool isValid(string s) {
        stack<char> brackets;
        int len = s.length();
        for (auto c : s) {
            if (c == '(' || c =='[' || c =='{') {
                brackets.push(c);
            }
            else if (brackets.empty() || (c - brackets.top() != 1 && c - brackets.top() != 2)) {
                return false;
            }
            else {
                brackets.pop();
            }
        }
        return brackets.empty();
    }
};

int main() {
    stack<int> s;
}


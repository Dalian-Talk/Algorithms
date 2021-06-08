#include <iostream>

using namespace std;


class Solution{
public:
    /*
     * 比较简单的一个处理。。是数字就返回
     * 这里数字的判定必须是叶子。。所以不用那么麻烦，直接看是不是叶子就行。。
     * 不是数字就对应处理就行。。
     */
    int evalTree(node* root) {
        // Your code here
        return dfs(root);
    }
private:
    int dfs(node* cur) {
        if (!cur->left && !cur->right) {
            return stoi(cur->data);
        }

        int left = dfs(cur->left);
        int right = dfs(cur->right);

        if (cur->data == "+") {
            return left + right;
        }
        if (cur->data == "-") {
            return left - right;
        }
        if (cur->data == "*") {
            return left * right;
        }
        return left / right;
    }

};
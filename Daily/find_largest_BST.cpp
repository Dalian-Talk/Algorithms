#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {

private:
    class Info {
    public:
        int min_val;
        int max_val;
        int num;
        bool is_bst;
        Info(int min_val, int max_val, int num, bool is_bst = false): min_val(min_val), max_val(max_val), num(num), is_bst(is_bst) {}
    };

public:
    // 这个写法就是要一直申请vector。。。空间复杂度爆炸了。。
    // 换另一个办法来传值回去
    int largestBSTSubtree(TreeNode* root) {
        int res = 0;
        dfs(root, res);
        return res;
    }

    vector<int> dfs(TreeNode* node, int& res) {
        if (!node) {
            return {1, INT_MAX, INT_MIN, 0};
        }

        vector<int> left = dfs(node->left, res);
        vector<int> right = dfs(node->right, res);

        if (left[0] && node->val > left[2] && right[0] && node->val < right[1]) {
            res = max(res, left[3] + right[3] + 1);
            return {1, min(node->val, left[1]), max(node->val, right[2]), left[3] + right[3] + 1};
        }

        return {0, 0, 0, 0};

    }


    /* 其实就是利用BST的特性从根往上找，只不过在处理上有很多取巧的地方。
     * 从上面的方法看，我记录了4个值，从左到右分别为:
     * 1、当前根节点对应子树是否为BST
     * 2、当前根节点对应子树的最小值 -> 用于作为右子树时进行判断
     * 3、当前根节点对应子树的最大值 -> 用于作为左子树诗进行判断
     * 4、当前根节点下最大BST子树的大小
     *
     * 这里看了个答案。在处理上可以少存一个值，通过 2 3这个最小最大值的设计，就能直接判断子树是否为合法的BST。原理是：
     * 如果某个根节点对应的子树是BST，那么该树的
     * 最小值一定是 {INT_MIN，某个节点的值}
     * 最大值一定是 {INT_MAX，某个节点的值}
     *
     * 那么对当前节点node与左右子树left, right进行判断的时候，就有以下一些情况
     * 若要让当前node成为一个BST那么:
     * 1、如果left是空，那么left是BST，我们需要让node->val > left.max
     * 2、如果left不是空，那么
     *      a、如果left是BST，我们需要让node->val > left.max
     *      b、如果left不是BST，我们需要让node->val <= left.max
     * 同理对于右子树
     * 3、如果right是空，那么right是BST，我们需要让node->val < right.max
     * 4、如果right不是空，那么
     *      a、如果right是BST，那么我们需要让node->val < right.min
     *      b、如果right不是BST，纳闷我们需要让node->val >= right.min
     *
     * 所以这里比较巧就巧在通过返回值的控制，能够让当前节点，直到下面的左右子树是否为BST
     *
     * Info 设计为 {子树最小值，子树最大值，最大BST子树的节点个数}
     *
     * 所以停止条件为
     * 1、如果node是空节点，那么返回{INT_MAX, INT_MIN, 0}。 这样子父节点可以比最大的(INT_MAX)大，比最小的(INT_MAX)小
     * 2、获取left和right子树
     *      如果node->val > left.max && node->val < right.min就代表当前node对应的整个树是个BST。正常的return就行了。
     *      这里return中间要更新一下当前子树的最大最小值(用node->val)虽然BST肯定是左边小的永远小，右边大的永远大。。。但是我们处理的时候为了方便，
     *      把空节点也返回了两个值(INT_MAX, INT_MIN)。 所以不更新的话就出问题啦。。。
     *
     *      如果不满足情况，就代表当前节点对应的子树不是BST，return的构造为
     *      {INT_MIN, INT_MAX, max(left.num, right.num)}
     *      这个意思就是，前两个在后续的判断中保证了子树不是BST，第三个参数就是当前子树下，最大的那个BST子树的大小。一步一步传到了最后的根节点。
     *
     *
     */

    int largestBSTSubtree1(TreeNode* root) {
        Info res = dfs1(root);
        return res.num;
    }


    Info dfs1(TreeNode* node) {
        if (!node) {
            return Info(INT_MAX, INT_MIN, 0);
        }

        Info left = dfs(node->left);
        Info right = dfs(node->right);

        if (node->val > left.max_val && node->val < right.min_val) {
            return Info(min(left.min_val, node->val), max(right.max_val, node->val), left.num + right.num + 1);
        }

        return Info(INT_MIN, INT_MAX, max(left.num, right.num));
    }

    // 下面这个方法其实就是把第二个方法的那种取巧的方式给展开了。
    // 根第一个方法一样，多存了一个是否是BST，用一个num的引用全程记录最大子树
    // 逻辑上看起来更舒服，但是效果是一样的。。。就是把用数值的比较改成了一个成员变量展示。。
    // 对于数值的设计 什么 INT_MIN, INT_MAX的要求就低了点。。不用想破头 23333

    int largestBSTSubtree2(TreeNode* root) {
        int num = 0;
        Info res = dfs2(root, num);
        return num;
    }


    Info dfs2(TreeNode* node, int& num) {
        if (!node) {
            return Info(INT_MAX, INT_MIN, 0, true);
        }

        Info left = dfs2(node->left, num);
        Info right = dfs2(node->right, num);

        if (left.is_bst && right.is_bst && node->val > left.max_val && node->val < right.min_val) {
            num = max(num, left.num + right.num + 1);
            return Info(min(left.min_val, node->val), max(right.max_val, node->val), left.num + right.num + 1, true);
        }

        return Info(INT_MIN, INT_MAX, 0, false);
    }



};




int main() {
    return 0;
}
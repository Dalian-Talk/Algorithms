/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    /*
     * 这里有点呆。。还想着省空间。直接merge在一个list上。。23333
     * 本来就是移动节点。。除了dummy的节点，其他的都是原本的节点。。只是换了位置。。又不是重新创建了节点。。
     * 根本不需要去纠结merge到l1 或者 l2上。。 脑子有点秀逗了。。缓缓。。。
     * 想inplace想疯了。。干。。明明空间复杂度一样的。。。
     *
     *
     *
     * 再有就是。链表的遍历方法。。要么用下面这种 l1 || l2 然后给特殊情况单独赋值
     *
     * 要么就是 l1 && l2出来之后把剩余的那个不是nullptr的接上就行。。
     * 根前面add two numbers类似。。
     * 就是处理的代码多和少的区别罢了。。。
     *
     * l1 || l2这种 整个循环逻辑上简洁点。。一个循环搞定。之后不用再单独判断了。。
     */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode();
        ListNode *p = dummy;
        while(l1 || l2) {
            int num1 = l1? l1->val: INT_MAX;
            int num2 = l2? l2->val: INT_MAX;
            if (num1 <= num2) {
                p->next = l1;
                l1 = l1->next;
            }
            else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        return dummy->next;
    }
};
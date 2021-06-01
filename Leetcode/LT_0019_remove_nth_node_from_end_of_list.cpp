#include <iostream>

using namespace std;


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
     * 一个数学技巧。 因为是要找到倒数第N个节点。正常做法就是。。走一遍算有几个 >> K个
     * 然后再从头走k - n步，然后跳过这个节点，就ok了。
     *
     * 所谓的one pass其实总时间和上面这个是一样的。。只不过就是。。one pass。。
     * 提前让一个指针p2走n步。这样子这个指针就根开头的指针p1岔开了n个节点。。
     * 然后让p1 p2一起走。
     * 当p2走到头，也就是nullptr后。。我们知道p1对应的节点倒数第n个节点了。跳过这个节点就行。 相当于一个数学上的小技巧吧。
     *
     * 那么这里我们只是把p1放在了倒数第n个节点。。我们希望跳过他。。所以应该让p1走到倒数第n + 1个节点。这样就好跳了。也就是所谓的要么让p2别走到nullptr。
     * 走到p2->next是nullptr就行。。要么是让p2提前多走一步，这样子我们就找到了倒数第n + 1个节点。效果是一样的。
     *
     *
     * 同样跟前面类似。这里用一个dummy节点指向头节点，在处理上会方便很多。。因为假设只有1个节点，一旦删了，就没了。。各种if else判断很烦。。
     * 但是有个头节点，在判断上会舒服、方便很多的。
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0, head);
        ListNode *p1 = dummy;
        ListNode *p2 = dummy->next; //提前走一步

        while (n) {
            p2 = p2->next;
            n--;
        }
        while (p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        p1->next = p1->next? p1->next->next : nullptr;

        return dummy->next;

    }
};
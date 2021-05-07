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
private:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 熟练掌握创建一个dummy head node这种方式，可以省去很多麻烦。
        ListNode *dummy_head = new ListNode();
        ListNode *l3 = dummy_head;
        int carry = 0;
        int sum = 0;

        while(l1 && l2) {
            sum = l1->val + l2->val + carry;
            carry = sum / 10;
            sum %= 10;
            l3->next = new ListNode(sum);
            l3 = l3->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while(l1) {
            sum = l1->val + carry;
            carry = sum / 10;
            sum %= 10;
            l3->next = new ListNode(sum);
            l3 = l3->next;
            l1 = l1->next;
        }
        while(l2) {
            sum = l2->val + carry;
            carry = sum / 10;
            sum %= 10;
            l3->next = new ListNode(sum);
            l3 = l3->next;
            l2 = l2->next;
        }
        if (carry) {
            l3->next = new ListNode(carry);
        }
        return dummy_head->next;
    }

    ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2) {
        // 对初始版本做代码简化、合并。 后续很多题目都有可能这种类型，不要写太冗余
        ListNode *dummy_head = new ListNode();
        ListNode *l3 = dummy_head;
        int carry = 0;
        int sum = 0;

        while(l1 || l2 || carry) {
            sum = (l1? l1->val : 0) + (l2? l2->val : 0) + carry;
            carry = sum / 10;
            sum %= 10;
            l3->next = new ListNode(sum);

            l1 = l1? l1->next : nullptr;
            l2 = l2? l2->next : nullptr;
            l3 = l3->next;
        }
        return dummy_head->next;
    }

};
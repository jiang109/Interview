class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        int carry = 0; // 进位
        // 只要 l1, l2 没走完，或者还有进位没处理完，就继续
        while (l1 || l2 || carry) {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;

            int sum = val1 + val2 + carry;
            carry = sum / 10; // 计算新的进位
            curr->next = new ListNode(sum % 10); // 创建当前位结果
            curr = curr->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        ListNode* res = dummy->next;
        delete dummy;
        return res;
    }
};
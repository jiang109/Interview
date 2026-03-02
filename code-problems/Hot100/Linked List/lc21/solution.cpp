class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                curr->next = list1;
                list1 = list1->next;
            }
            else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }
        curr->next = (list1 != nullptr) ? list1 : list2;
        ListNode* head = dummy->next;
        delete dummy; 
        return head;
    }
};
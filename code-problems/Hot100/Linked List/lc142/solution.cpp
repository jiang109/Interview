class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (!head || !head->next) return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCycle = false;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        if (hasCycle) {
            ListNode* ptr = head; 
            while (ptr != slow) { 
                ptr = ptr->next;
                slow = slow->next;
            }
            return ptr; 
        }

        return nullptr;
    }
};
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

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

int main() {
    int n, pos;
    while (cin >> n >> pos) {
        if (n == 0) {
            cout << "null" << endl;
            continue;
        }

        vector<ListNode*> nodes;
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            ListNode* newNode = new ListNode(val);
            tail->next = newNode;
            tail = newNode;
            nodes.push_back(newNode);
        }

        if (pos != -1 && pos < n) {
            tail->next = nodes[pos];
        }

        Solution sol;
        ListNode* result = sol.detectCycle(dummy->next);

        if (result) {

            cout << "tail connects to node with value: " << result->val << endl;
        }
        else {
            cout << "no cycle" << endl;
        }

        // 释放内存前断开环
        tail->next = nullptr;
        for (auto node : nodes) delete node;
        delete dummy;
    }
    return 0;
}
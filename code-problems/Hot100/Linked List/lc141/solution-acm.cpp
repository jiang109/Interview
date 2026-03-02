#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (!head || !head->next) return false;
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

int main() {
    
    int n, pos;
    // 假设输入格式：先输入节点总数 n，再输入连接位置 pos，最后输入 n 个节点的值
    while (cin >> n >> pos) {
        if (n == 0) {
            cout << "false" << endl;
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

        if (pos != -1 && pos < (int)nodes.size()) {
            tail->next = nodes[pos]; // 尾节点连向指定的 pos 索引节点
        }
        Solution sol;
        if (sol.hasCycle(dummy->next)) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }
        tail->next = nullptr;
        for (ListNode* node : nodes) {
            delete node;
        }
        delete dummy;
    }

    return 0;
}
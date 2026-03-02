#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        Node* curr = head;
        while (curr) {
            Node* newNode = new Node(curr->val);
            newNode->next = curr->next;
            curr->next = newNode;
            curr = newNode->next;
        }

        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }
        Node* res = head->next;
        Node* copyCurr = res;
        curr = head;
        while (curr) {
            curr->next = curr->next->next;
            if (copyCurr->next) {
                copyCurr->next = copyCurr->next->next;
            }
            curr = curr->next;
            copyCurr = copyCurr->next;
        }
        return res;
    }
};

Node* buildList(vector<pair<int, int>> data) {
    if (data.empty()) return nullptr;
    vector<Node*> nodes;
    for (auto& p : data) {
        nodes.push_back(new Node(p.first));
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (i < nodes.size() - 1) nodes[i]->next = nodes[i + 1];
        if (data[i].second != -1) { // -1 ±íÊ¾ null
            nodes[i]->random = nodes[data[i].second];
        }
    }
    return nodes[0];
}

void printList(Node* head) {
    Node* curr = head;
    unordered_map<Node*, int> nodeToIndex;
    Node* temp = head;
    int idx = 0;
    while (temp) {
        nodeToIndex[temp] = idx++;
        temp = temp->next;
    }

    cout << "[";
    curr = head;
    while (curr) {
        cout << "[" << curr->val << ",";
        if (curr->random) cout << nodeToIndex[curr->random];
        else cout << "null";
        cout << "]";
        if (curr->next) cout << ",";
        curr = curr->next;
    }
    cout << "]" << endl;
}

int main() {
    
    vector<pair<int, int>> input = { {7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0} };

    cout << "Original List: ";
    Node* head = buildList(input);
    printList(head);

    Solution sol;
    Node* copiedHead = sol.copyRandomList(head);

    cout << "Copied List:   ";
    printList(copiedHead);

    return 0;
}
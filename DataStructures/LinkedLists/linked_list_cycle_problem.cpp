// HASHSET SOLUTION TO LINKED LIST CYCLE PROBLEM

#include <iostream>
#include <unordered_set>
#include <string>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
    public:
        bool hashSet_hasCycle(ListNode *head) {
        std::unordered_set<ListNode*> visited; // Hashset
        
        while(head != NULL)
        {
            if (visited.find(head) != visited.end()) return true;
            visited.insert(head);
            head = head->next;
        }
        
        return false;
    }
    bool tortoiseAndHare_hasCycle(ListNode *head) { 
        // Space --> O(1)
        // Time --> O(N)
        ListNode* fast = head;
        ListNode* slow = head;
        
        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) return true;
        }
        return false;
    }
};

int main()
{
}
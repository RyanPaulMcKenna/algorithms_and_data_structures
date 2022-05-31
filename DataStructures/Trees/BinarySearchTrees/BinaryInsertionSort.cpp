// Online C++ compiler to run C++ program online
#include <iostream>

class TreeNode {
    public:
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        int key;
        TreeNode(int key): key{key}, left{nullptr},right{nullptr}, parent{nullptr} {}
};

void insert(TreeNode* root, TreeNode* z) 
{
    TreeNode* y = nullptr;
    TreeNode* x = root;
    
    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    if (y == nullptr)
    {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
};
void inorderWalk(TreeNode* root) {
    if (root != nullptr) {
        inorderWalk(root->left);
        std::cout << root->key << " ";
        inorderWalk(root->right);
    }
};
int main() {
    
    int arr[] = {0,5,2,9,6,9,32,1,-4,5,7-21,6};
    int sz = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = new TreeNode(arr[0]);
    for (int i = 1; i < sz; ++i)
    {
        TreeNode* newNode = new TreeNode(arr[i]);
        insert(root, newNode);
    }
    inorderWalk(root);

    return 0;
}
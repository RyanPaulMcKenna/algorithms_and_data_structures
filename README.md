# Algorithms and data structures and design patterns

My implementations of various standard algorithms, datastructures and design patterns in C++.

Folders structured as follows:
* algos_and_ds
    * DataStructures
    * DynamicProgramming
    * Selection
    * Sorting
* design_patterns
    * Chapter1
    * Chapter2
    * Chapter3
    * Chapter4
    * DesignPatterns
        * behavioural_patterns
        * creational_patterns
        * structural_patterns
* refactoring/Code Smells

```c++
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

```


Copyright 2023 Ryan Paul McKenna

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

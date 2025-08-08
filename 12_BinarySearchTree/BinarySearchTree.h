#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct TreeNode
{
    TreeNode(int val) : key(val), left(nullptr), right(nullptr){}
    int key;
    TreeNode* left;
    TreeNode* right;
};

class BinarySearchTree
{
private:
    
public:
    BinarySearchTree(int val);
    BinarySearchTree(vector<int> va_list);
    ~BinarySearchTree();

    void insert(int val);
    void insert(vector<int> vals);

    void Inorder_tree_walk(TreeNode* x)
    {
        if (x != nullptr)
        {
            Inorder_tree_walk(x->left);
            cout << x->key << " ";
            Inorder_tree_walk(x->right);
        }
    }

    void preorder_tree_walk(TreeNode* x)
    {
        if (x != nullptr)
        {
            cout << x->key << " ";
            preorder_tree_walk(x->left);
            preorder_tree_walk(x->right);
        }
    }

    void postorder_tree_walk(TreeNode* x)
    {
        if (x != nullptr)
        {
            postorder_tree_walk(x->left);
            postorder_tree_walk(x->right);
            cout << x->key << " ";
        }
    }

    void deleteTree(TreeNode* node);
public:
    TreeNode* m_root = nullptr;
};

BinarySearchTree::BinarySearchTree(int val)
{
    m_root = new TreeNode(val);
}

BinarySearchTree::BinarySearchTree(vector<int> va_list)
{
    for (const int val : va_list)
    {
        insert(val);
    }
}

BinarySearchTree::~BinarySearchTree()
{
    deleteTree(m_root);
}

void BinarySearchTree::insert(int val)
{
    if (m_root == nullptr)
    {
        m_root = new TreeNode(val);
        return;
    }

    bool success_insert = false;
    TreeNode* cur_node = m_root;
    while (!success_insert)
    {
        if (val < cur_node->key)
        {
            if (cur_node->left == nullptr)
            {
                cur_node->left = new TreeNode(val);
                success_insert = true;
            }
            else
            {
                cur_node = cur_node->left;
            }
        }
        else
        {
            if (cur_node->right == nullptr)
            {
                cur_node->right = new TreeNode(val);
                success_insert = true;
            }
            else
            {
                cur_node = cur_node->right;
            }
        }
    }
}

void BinarySearchTree::insert(vector<int> vals)
{
    for (const int val : vals)
        insert(val);
}

void BinarySearchTree::deleteTree(TreeNode* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}



#endif
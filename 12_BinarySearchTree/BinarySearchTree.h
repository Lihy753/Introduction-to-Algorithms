#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct TreeNode
{
    TreeNode(int val) : key(val), left(nullptr), right(nullptr), parent(nullptr){}
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
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

//12.2  query
    TreeNode* tree_search(TreeNode* root, int key);
    
    TreeNode* iterative_tree_search(TreeNode* root, int key);

    TreeNode* tree_minimum(TreeNode* root);

    TreeNode* tree_maximum(TreeNode* root);

    //后继与前驱， 即节点 x 的后一个节点与前一个节点；
    TreeNode* tree_successor(TreeNode* x);
    TreeNode* tree_predecessor(TreeNode* x);

//12.3
    void tree_insert(TreeNode* z);
    void transplant(TreeNode* u, TreeNode* v);
    void tree_delete(TreeNode* z);

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
                cur_node->left->parent = cur_node;
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
                cur_node->right->parent = cur_node;
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

//12.2
TreeNode* BinarySearchTree::tree_search(TreeNode* root, int key)
{
    if (root == nullptr || key == root->key)
        return root;
    
    if (key < root->key)
        return tree_search(root->left, key);
    else
        return tree_search(root->right, key);
}

TreeNode* BinarySearchTree::iterative_tree_search(TreeNode* root, int key)
{
    while (root != nullptr && key != root->key)
    {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

TreeNode* BinarySearchTree::tree_minimum(TreeNode* root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

TreeNode* BinarySearchTree::tree_maximum(TreeNode* root)
{
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root;
}

TreeNode* BinarySearchTree::tree_successor(TreeNode* x)
{
    if (x->right != nullptr)
        return tree_minimum(x->right);
    
    TreeNode* y = x->parent;
    while (y != nullptr && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

TreeNode* BinarySearchTree::tree_predecessor(TreeNode* x)
{
    if (x->left != nullptr)
        return tree_maximum(x->left);
    
    TreeNode* y = x->parent;
    while (y != nullptr && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

//12.3
void BinarySearchTree::tree_insert(TreeNode* z)
{
    TreeNode* y = nullptr;
    TreeNode* x = m_root;
    while (x != nullptr)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        m_root = y;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

void BinarySearchTree::transplant(TreeNode* u, TreeNode* v)
{
    if (u->parent == nullptr)
        m_root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

void BinarySearchTree::tree_delete(TreeNode* z)
{   
    if (z->left == nullptr)
        transplant(z, z->right);
    else if (z->right == nullptr)
        transplant(z, z->left);
    else 
    {
        TreeNode* y = tree_minimum(z->right);
        if (y->parent != z)
        {
            transplant(z, z->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

#endif
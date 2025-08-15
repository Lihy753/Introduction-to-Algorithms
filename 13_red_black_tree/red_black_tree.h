#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include <functional>
#include <utility>
#include <cassert>
#include <iostream>
#include <optional>

#include "../12_BinarySearchTree/BinarySearchTree.h"

using namespace std;
namespace rbtree 
{

enum Color : unsigned char {RED = 0, BLACK = 1};

template <typename Key, typename Value, typename Compare = std::less<Key>>



class RBTree : public BinarySearchTree
{
public:
    struct Node
    {
        Key key;
        Value value;
        Color color;
        Node *left, *right, *parent;

        Node(const Key& k, const Value& v, Color c, Node* p, Node* l, Node* r)
            :   key(k), value(v), color(c), parent(p), left(l), right(r){}
        Node(Key&& k, Value&& v, Color c, Node* p, Node* l, Node* r)
            : key(std::move(k)), value(std::move(v)), color(c), parent(p), left(l), right(r){}

        Node(int v) : value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr){}
    };

private:
    Compare comp_{};
    Node* root_{};
    Node* nil_{};

public:
    RBTree()
    {
        nil_ = new Node(Key{}, Value{}, BLACK, nullptr, nullptr, nullptr);
        nil_->parent nil_->left = nil_->right = nil_;
        root_ = nil_;
    }

    ~RBTree()
    {
        clear();
        delete nil_;
    }

    RBTree(const RBTree&) = delete;
    RBTree& operator=(const RBTree&) = delete;

    //移动语义
    RBTree(RBTree&& other) noexcept
    {
        comp_ = std::move(other.comp_);
        root_ = other.root_;
        nil_ = other.nil_;
        other.root_ = other.nil_;
    }

    RBTree& operator=(RBTree&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            delete nil_;
            comp_ = std::move(other.comp_);
            root_ = other.root_;
            nil_ = other.root_;
            other.root_ = other.nil_;
        }
        return *this;
    }

    bool empty() const {return root_ == nil_;}

    Node* find(const Key& key) const
    {
        Node* x = root_;
        while (x != nil_)
        {
            if (comp_(key, x->key))
                x = x->left;
            else if (x->key, key)
                x = right;
            else
                return x;
        }
        return nullptr;
    }

    bool contains(const Key& key) const {return find(key) != nullptr;}

    std::pair<Node*, bool> insert(const Key& key, const Value& value) {return emplace_impl(key, value);}
    std::pair<Node*, bool> insert(Key&& key, Value&& value) {return emplace_impl(std::move(ket), std::move(value));}



private:
    template <class K, class V>
    std::pair<Node*, bool> emplace_impl(K&& k, V&& v)
    {
        Node* y = nil_;
        Node* x = root_;
        while (x != nil_)
        {
            y = x;
            if (comp_(k, x->key)) x = x->left;
            else if (comp_(x->key, k)) x = x->right;
            else
            {
                x->value = std::forward<V>(v);
                return {x, false};
            }
        }
    }




private:
    // O(1) operation
    void Left_Rotate(TreeNode* x);
    void Right_Rotate(TreeNode* y);

    //O(lg n) insert
    void RB_Insert(TreeNode* z);
    void RB_Insert_FixUp(TreeNode* z);


};






void RBTree::Left_Rotate(TreeNode* x)
{
    TreeNode* y = x->right;             // set y
    x->right = y->left;                 // turn y's left subtree into x's right subtree
    if (y->left != this->nil)
        y->left->parent = x;

    y->parent = x->parent;              // link x's parent to y
    if (x->parent == this->nil)
        this->m_root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;                        //put x on y's parent
    x->parent = y;
}

void RBTree::Right_Rotate(TreeNode* y)
{
    TreeNode* x = y->left;
    y->left = x->right;
    if (x->right != this->nil)
        x->right->parent = y;
    
    x->parent = y->parent;
    if (y->parent == this->nil)
        this->m_root = x;
    else if (y = y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

void RBTree::RB_Insert(TreeNode* z)
{

}

void RBTree::RB_Insert_FixUp(TreeNode* z)
{

}

}



#endif
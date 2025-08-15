// RedBlackTree.hpp — 带哨兵(nil)哨兵节点的红黑树（C++17）
// 特点：
//  - 单例 BLACK 哨兵节点，所有空子树与根的父指针均指向它
//  - 插入/删除/查找/中序遍历/验证接口
//  - 模板支持可比较 Key 与任意 Value（可当 set 使用：Value=std::monostate 或不关心 value）
//  - 无异常分配后即拥有，析构安全释放
//  - 只依赖 <functional>, <utility>, <cassert>, <iostream>

#pragma once
#include <functional>
#include <utility>
#include <cassert>
#include <iostream>
#include <optional>

namespace rbtree {

enum Color : unsigned char { RED = 0, BLACK = 1 };

template <typename Key, typename Value, typename Compare = std::less<Key>>
class RedBlackTree {
public:
    struct Node {
        Key key;            // 关键字
        Value value;        // 值
        Color color;        // 颜色
        Node* parent;       // 父
        Node* left;         // 左
        Node* right;        // 右

        Node(const Key& k, const Value& v, Color c, Node* p, Node* l, Node* r)
            : key(k), value(v), color(c), parent(p), left(l), right(r) {}
        Node(Key&& k, Value&& v, Color c, Node* p, Node* l, Node* r)
            : key(std::move(k)), value(std::move(v)), color(c), parent(p), left(l), right(r) {}
    };

private:
    Compare comp_{};
    Node* root_{};
    Node* nil_; // 单例哨兵（BLACK）

public:
    RedBlackTree() {
        nil_ = new Node(Key{}, Value{}, BLACK, nullptr, nullptr, nullptr);
        nil_->parent = nil_->left = nil_->right = nil_; // 自环，便于判空
        root_ = nil_;
    }

    ~RedBlackTree() {
        clear();
        delete nil_;
    }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    // 移动语义（可选）
    RedBlackTree(RedBlackTree&& other) noexcept {
        comp_ = std::move(other.comp_);
        root_ = other.root_;
        nil_ = other.nil_;
        other.root_ = other.nil_;
    }
    RedBlackTree& operator=(RedBlackTree&& other) noexcept {
        if (this != &other) {
            clear();
            delete nil_;
            comp_ = std::move(other.comp_);
            root_ = other.root_;
            nil_ = other.nil_;
            other.root_ = other.nil_;
        }
        return *this;
    }

    bool empty() const { return root_ == nil_; }

    // 查找：返回节点指针，若未找到返回 nullptr
    Node* find(const Key& key) const {
        Node* x = root_;
        while (x != nil_) {
            if (comp_(key, x->key)) x = x->left;
            else if (comp_(x->key, key)) x = x->right;
            else return x; // equal
        }
        return nullptr;
    }

    bool contains(const Key& key) const { return find(key) != nullptr; }

    // 插入：若 key 已存在则更新 value，返回 pair(节点*, 是否新插入)
    std::pair<Node*, bool> insert(const Key& key, const Value& value) {
        return emplace_impl(key, value);
    }
    std::pair<Node*, bool> insert(Key&& key, Value&& value) {
        return emplace_impl(std::move(key), std::move(value));
    }

    // 删除：根据 key，返回是否删除成功
    bool erase(const Key& key) {
        Node* z = node_for_key(key);
        if (!z) return false;
        erase_node(z);
        return true;
    }

    // 清空
    void clear() {
        // 后序释放所有非哨兵节点
        postorder_delete(root_);
        root_ = nil_;
    }

    // 中序遍历输出（调试）
    void inorder_dump(std::ostream& os = std::cout) const {
        inorder_visit(root_, [&](Node* n){
            os << n->key << ":" << n->value << (n->color==RED?"(R)":"(B)") << " ";
        });
        os << "\n";
    }

    // 验证红黑性质，返回 (是否有效, 黑高)
    std::pair<bool,int> validate() const {
        if (root_ == nil_) return {true, 1};
        if (root_->color != BLACK) return {false, -1};
        int bh = -1;
        bool ok = validate_recur(root_, 0, bh);
        return {ok, bh};
    }

    // 最小键值节点
    Node* minimum(Node* x) const {
        while (x->left != nil_) x = x->left;
        return x;
    }

    Node* maximum(Node* x) const {
        while (x->right != nil_) x = x->right;
        return x;
    }

    Node* root() const { return root_ == nil_ ? nullptr : root_; }
    Node* nil() const { return nil_; }

private:
    template <class K, class V>
    std::pair<Node*, bool> emplace_impl(K&& k, V&& v) {
        Node* y = nil_;
        Node* x = root_;
        while (x != nil_) {
            y = x;
            if (comp_(k, x->key)) x = x->left;
            else if (comp_(x->key, k)) x = x->right;
            else { // equal -> update value
                x->value = std::forward<V>(v);
                return {x, false};
            }
        }
        Node* z = new Node(std::forward<K>(k), std::forward<V>(v), RED, y, nil_, nil_);
        if (y == nil_) {
            root_ = z;
        } else if (comp_(z->key, y->key)) {
            y->left = z;
        } else {
            y->right = z;
        }
        insert_fixup(z);
        return {z, true};
    }

    Node* node_for_key(const Key& key) const {
        Node* x = root_;
        while (x != nil_) {
            if (comp_(key, x->key)) x = x->left;
            else if (comp_(x->key, key)) x = x->right;
            else return x;
        }
        return nullptr;
    }

    void left_rotate(Node* x) {
        Node* y = x->right;        // set y
        assert(y != nil_);
        x->right = y->left;        // turn y's left subtree into x's right subtree
        if (y->left != nil_) y->left->parent = x;
        y->parent = x->parent;     // link x's parent to y
        if (x->parent == nil_) root_ = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;               // put x on y's left
        x->parent = y;
    }

    void right_rotate(Node* y) {
        Node* x = y->left;
        assert(x != nil_);
        y->left = x->right;
        if (x->right != nil_) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nil_) root_ = x;
        else if (y == y->parent->right) y->parent->right = x;
        else y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    void insert_fixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right; // 叔父
                if (y->color == RED) {
                    // Case 1: 叔父 RED -> 重染色，向上继续
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: 内侧 -> 先左旋
                        z = z->parent;
                        left_rotate(z);
                    }
                    // Case 3: 外侧 -> 右旋并重染色
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                // 对称情形
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root_->color = BLACK;
        root_->parent = nil_; // 根的父也指向哨兵，便于统一处理
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nil_) root_ = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    void erase_node(Node* z) {
        Node* y = z;
        Color y_orig_color = y->color;
        Node* x = nullptr;
        if (z->left == nil_) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil_) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right); // 后继
            y_orig_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y; // 可能是哨兵
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_orig_color == BLACK) erase_fixup(x);
    }

    void erase_fixup(Node* x) {
        while (x != root_ && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right; // 兄弟
                if (w->color == RED) { // Case 1
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) { // Case 2
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) { // Case 3
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    // Case 4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = root_;
                }
            } else {
                // 对称
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = root_;
                }
            }
        }
        x->color = BLACK;
    }

    void inorder_visit(Node* x, const auto& fn) const {
        if (x == nil_) return;
        inorder_visit(x->left, fn);
        fn(x);
        inorder_visit(x->right, fn);
    }

    void postorder_delete(Node* x) {
        if (x == nil_) return;
        postorder_delete(x->left);
        postorder_delete(x->right);
        if (x != nil_) delete x;
    }

    bool validate_recur(Node* x, int black_cnt, int& black_height) const {
        if (x->color == BLACK) ++black_cnt;
        if (x == nil_) {
            if (black_height == -1) black_height = black_cnt;
            return black_cnt == black_height;
        }
        // 红节点不能有红孩子
        if (x->color == RED) {
            if (x->left->color == RED || x->right->color == RED) return false;
        }
        return validate_recur(x->left, black_cnt, black_height) &&
               validate_recur(x->right, black_cnt, black_height);
    }
};

} // namespace rbtree




int main() {
    using Tree = rbtree::RedBlackTree<int, int>;
    Tree t;
    for (int x : {10, 20, 30, 15, 25, 5, 1, 50, 60, 55}) t.insert(x, x*10);
    t.inorder_dump();
    auto [ok, bh] = t.validate();
    std::cout << "valid=" << ok << ", black_height=" << bh << "\n";

    t.erase(20);
    t.erase(10);
    t.inorder_dump();
    std::tie(ok, bh) = t.validate();
    std::cout << "valid=" << ok << ", black_height=" << bh << "\n";

    if (auto n = t.find(25)) std::cout << "25=>" << n->value << "\n";
}


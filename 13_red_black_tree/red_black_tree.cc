#include "red_black_tree.h"



int main() {
    using Tree = rbtree::RBTree<int, int>;
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
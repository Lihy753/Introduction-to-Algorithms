#include "BinarySearchTree.h"


int main()
{
    int val = 15;
    std::vector<int> val_list{15, 6, 3, 2, 4, 7, 13, 9, 18, 17, 20};

    BinarySearchTree binary_tree(val_list);
    binary_tree.Inorder_tree_walk(binary_tree.m_root);
    std::cout << std::endl;
    binary_tree.preorder_tree_walk(binary_tree.m_root);
    std::cout << std::endl;
    binary_tree.postorder_tree_walk(binary_tree.m_root);

    
    return 0;
}
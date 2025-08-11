#include "BinarySearchTree.h"


int main()
{
    int val = 15;
    std::vector<int> val_list{15, 6, 3, 2, 4, 7, 13, 9, 18, 17, 20};

    BinarySearchTree binary_tree(val_list);
    TreeNode* root = binary_tree.m_root;
    binary_tree.Inorder_tree_walk(root);
    std::cout << std::endl;
    binary_tree.preorder_tree_walk(root);
    std::cout << std::endl;
    binary_tree.postorder_tree_walk(root);
    std::cout << std::endl;
    TreeNode* result = binary_tree.tree_search(root, 3);
    std::cout << "result.key " << result->key << endl;
    std::cout << "result->left.key " << result->left->key << endl;
    std::cout << "result->right.key " << result->right->key << endl;
    std::cout << "result->parent.key " << result->parent->key << endl;

    TreeNode* result_2 = binary_tree.iterative_tree_search(root, 3);
    std::cout << "result_2.key " << result_2->key << endl;
    std::cout << "result_2->left.key " << result_2->left->key << endl;
    std::cout << "result_2->right.key " << result_2->right->key << endl;
    std::cout << "result->parent.key " << result->parent->key << endl;

    TreeNode* min_res = binary_tree.tree_minimum(root);
    TreeNode* max_res = binary_tree.tree_maximum(root); 
    std::cout << "min_key " << min_res->key << ", max_res " << max_res->key << std::endl;

    TreeNode* node = binary_tree.tree_search(root, 13);
    TreeNode* result_3 = binary_tree.tree_successor(node);
    std::cout << "result_3.key " << result_3->key << std::endl;

    // //这里虽然让 root = 18 的子树挪了过来，但是原本的位置仍然能够遍历到!
    // TreeNode* node_1 = binary_tree.tree_search(root, 13);
    // TreeNode* node_2 = binary_tree.tree_search(root, 18);
    // binary_tree.transplant(node_1, node_2);
    // binary_tree.Inorder_tree_walk(root);
    // std::cout << std::endl;

    TreeNode* node_3 = binary_tree.tree_search(root, 7);
    binary_tree.tree_delete(node_3);
    binary_tree.Inorder_tree_walk(root);
    std::cout << std::endl;

    

    return 0;
}
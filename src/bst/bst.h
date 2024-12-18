#ifndef BST_H
#define BST_H

typedef struct TreeNode {
    void *content;
    const char *key;

    struct TreeNode *right;
    struct TreeNode *left;
} TreeNode;

TreeNode *tree_insert(TreeNode *root, const char *key, void *content);

TreeNode *tree_delete_node(TreeNode *root, const char *key);

TreeNode *tree_search_node(TreeNode *root, const char *key);

#endif

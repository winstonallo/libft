#ifndef BTREE_H
#define BTREE_H

typedef struct TreeNode {
    void *content;
    const char *key;

    struct TreeNode *right;
    struct TreeNode *left;
} TreeNode;

TreeNode *tree_new_node(const char *key, void *content);

void tree_insert(TreeNode **root, TreeNode *node);

#endif

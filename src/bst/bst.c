#include "bst.h"
#include "alloc.h"
#include "mem.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

__attribute__((always_inline)) static inline TreeNode *
tree_new_node(const char *key, void *content) {

    TreeNode *new_node = ft_calloc(1, sizeof(TreeNode));
    if (!new_node) {
        return NULL;
    }

    new_node->key = key;
    new_node->content = content;

    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

TreeNode *
tree_insert(TreeNode *root, const char *key, void *content) {

    TreeNode *new_node = tree_new_node(key, content);
    if (!new_node) {
        return NULL;
    }

    if (!root) {
        return new_node;
    }

    TreeNode *parent = NULL;
    TreeNode *it = root;

    while (it) {
        parent = it;

        int diff = ft_memcmp(it->key, new_node->key, ft_strlen(new_node->key) + 1);

        if (diff > 0) {
            it = it->left;
        } else if (diff < 0) {
            it = it->right;
        } else {
            return it;
        }
    }

    if (ft_memcmp(parent->key, new_node->key, ft_strlen(new_node->key) + 1) > 0) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    return root;
}

TreeNode *
find_min(TreeNode *node) {

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}
TreeNode *
tree_delete_node(TreeNode *root, const char *key) {
    if (!root) {
        return NULL;
    }

    int diff = ft_memcmp(root->key, key, ft_strlen(key) + 1);

    if (diff > 0) {
        root->left = tree_delete_node(root->left, key);
    } else if (diff < 0) {
        root->right = tree_delete_node(root->right, key);
    } else {

        if (!root->left && !root->right) {
            free(root);
            return NULL;
        } else if (!root->left) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        } else {
            TreeNode *successor = find_min(root->right);

            root->content = successor->content;

            root->right = tree_delete_node(root->right, successor->key);
        }
    }

    return root;
}

TreeNode *
tree_search_node(TreeNode *root, const char *key) {
    if (!root) {
        return root;
    }

    short diff = ft_memcmp(root->key, key, ft_strlen(key) + 1);
    if (diff > 0) {
        return tree_search_node(root->left, key);
    } else if (diff < 0) {
        return tree_search_node(root->right, key);
    } else {
        return root;
    }
}

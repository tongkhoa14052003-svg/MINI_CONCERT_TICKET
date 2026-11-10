
#ifndef BST_H
#define BST_H

#include "Product.h"

struct BSTNode {
    Product data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Product& product);
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertNode(BSTNode* node, const Product& product);
    BSTNode* searchNode(BSTNode* node, int id) const;
    BSTNode* deleteNode(BSTNode* node, int id);
    BSTNode* findMin(BSTNode* node) const;

    void inorderTraversal(BSTNode* node) const;
    void preorderTraversal(BSTNode* node) const;
    void postorderTraversal(BSTNode* node) const;

    void clear(BSTNode* node);

public:
    BST();
    ~BST();

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const Product& product);
    Product* search(int id);
    bool remove(int id);

    void inorder() const;
    void preorder() const;
    void postorder() const;

    void clear();
};

#endif

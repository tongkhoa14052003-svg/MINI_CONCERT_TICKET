
#include "BST.h"

#include <iostream>

BSTNode::BSTNode(const Product& product)
    : data(product), left(nullptr), right(nullptr) {
}

BST::BST() : root(nullptr) {
}

BST::~BST() {
    clear();
}

BSTNode* BST::insertNode(
    BSTNode* node,
    const Product& product
) {
    if (node == nullptr) {
        return new BSTNode(product);
    }

    if (product.id < node->data.id) {
        node->left = insertNode(node->left, product);
    } else if (product.id > node->data.id) {
        node->right = insertNode(node->right, product);
    }

    return node;
}

void BST::insert(const Product& product) {
    root = insertNode(root, product);
}

BSTNode* BST::searchNode(
    BSTNode* node,
    int id
) const {
    if (node == nullptr || node->data.id == id) {
        return node;
    }

    if (id < node->data.id) {
        return searchNode(node->left, id);
    }

    return searchNode(node->right, id);
}

Product* BST::search(int id) {
    BSTNode* result = searchNode(root, id);

    if (result == nullptr) {
        return nullptr;
    }

    return &result->data;
}

BSTNode* BST::findMin(BSTNode* node) const {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }

    return node;
}

BSTNode* BST::deleteNode(
    BSTNode* node,
    int id
) {
    if (node == nullptr) {
        return nullptr;
    }

    if (id < node->data.id) {
        node->left = deleteNode(node->left, id);
    } else if (id > node->data.id) {
        node->right = deleteNode(node->right, id);
    } else {
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        BSTNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(
            node->right,
            successor->data.id
        );
    }

    return node;
}

bool BST::remove(int id) {
    if (search(id) == nullptr) {
        return false;
    }

    root = deleteNode(root, id);
    return true;
}

void BST::inorderTraversal(BSTNode* node) const {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    displayProduct(node->data);
    inorderTraversal(node->right);
}

void BST::preorderTraversal(BSTNode* node) const {
    if (node == nullptr) {
        return;
    }

    displayProduct(node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void BST::postorderTraversal(BSTNode* node) const {
    if (node == nullptr) {
        return;
    }

    postorderTraversal(node->left);
    postorderTraversal(node->right);
    displayProduct(node->data);
}

void BST::inorder() const {
    std::cout << "\nBST INORDER\n";
    inorderTraversal(root);
}

void BST::preorder() const {
    std::cout << "\nBST PREORDER\n";
    preorderTraversal(root);
}

void BST::postorder() const {
    std::cout << "\nBST POSTORDER\n";
    postorderTraversal(root);
}

void BST::clear(BSTNode* node) {
    if (node == nullptr) {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
}

void BST::clear() {
    clear(root);
    root = nullptr;
}

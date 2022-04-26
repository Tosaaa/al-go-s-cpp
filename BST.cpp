#include <iostream>
#include <vector>

using namespace std;

class TreeNode {
   public:
    int val;
    int n;  // # of nodes (including node itself)
    TreeNode *left;
    TreeNode *right;
    TreeNode(int _val = 0, TreeNode *_left = NULL, TreeNode *_right = NULL) {
        this->val = _val;
        this->n = 1;
        this->left = _left;
        this->right = _right;
    }
};

class BinaryTree {
   private:
    TreeNode *root;

    int getN(TreeNode *root) {
        if (root == NULL) return 0;
        return root->n;
    }

    TreeNode *addNodeUtil(TreeNode *root, int _val) {
        if (root == NULL) {
            TreeNode *node = new TreeNode(_val);
            return node;
        } else if (root->val > _val) {
            root->left = addNodeUtil(root->left, _val);
        } else if (root->val < _val) {
            root->right = addNodeUtil(root->right, _val);
        }
        root->n = getN(root->left) + getN(root->right) + 1;
        return root;
    }

    TreeNode *getNodeUtil(TreeNode *root, int _val) {
        if (root == NULL) {
            return NULL;
        } else if (root->val > _val) {
            return getNodeUtil(root->left, _val);
        } else if (root->val < _val) {
            return getNodeUtil(root->right, _val);
        } else if (root->val == _val) {
            return root;
        }
        return root;  // 사실 필요 X
    }

    void printInorderUtil(TreeNode *root) {
        if (root == NULL) return;
        printInorderUtil(root->left);
        cout << root->val << " " << root->n << endl;
        printInorderUtil(root->right);
    }

    void delTree(TreeNode *root) {
        if (root == NULL) return;
        delTree(root->left);
        delTree(root->right);
        delete root;
    }

   public:
    BinaryTree(int _val) {
        root = new TreeNode(_val);
    }

    BinaryTree() {
        root = NULL;
    }

    ~BinaryTree() {
        delTree(root);
    }

    TreeNode *getRoot() {
        return root;
    }

    int getSize() {
        return root->n;
    }

    void addNode(int _val) {
        root = addNodeUtil(root, _val);
    }

    TreeNode *getNode(int _val) {
        return getNodeUtil(root, _val);
    }

    bool isExist(int _val) {
        if (getNodeUtil(root, _val) == NULL) {
            return false;
        }
        return true;
    }

    void printInorder() {
        printInorderUtil(root);
    }
    // void delNode();
};

// int main() {
//     BinaryTree *bst = new BinaryTree(9);
//     bst->addNode(5);
//     bst->addNode(3);
//     bst->addNode(7);
//     bst->addNode(3);
//     bst->addNode(100);
//     bst->printInorder();
//     cout << "getSize: " << bst->getSize() << endl;
//     TreeNode *node = bst->getNode(3);

//     delete bst;

//     return 0;
// }
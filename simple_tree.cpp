#include <iostream>
#include <vector>

#define REP(i, a, b) for (int(i) = (a); (i) < (b); (i)++)
#define endl '\n'

using namespace std;

class TreeNode {
   public:
    int val;
    int n;  // # of child nodes
    TreeNode *left;
    TreeNode *right;
    TreeNode(int _val = 0, TreeNode *_left = NULL, TreeNode *_right = NULL) {
        this->val = _val;
        this->left = _left;
        this->right = _right;
    }
};

void inorder(TreeNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->val << endl;
    inorder(root->right);
}

void preorder(TreeNode *root) {
    if (root == NULL) return;
    cout << root->val << endl;
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    TreeNode *root = new TreeNode(1);
    TreeNode *child1 = new TreeNode(2);
    TreeNode *child2 = new TreeNode(3);

    root->left = child1;
    root->right = child2;

    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
    postorder(root);
    cout << endl;
    return 0;
}
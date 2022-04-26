// Segment tree

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

#define REP(i, a, b) for (int i = a; i < b; i++)
#define endl '\n'

class TreeNode {
   public:
    int val;
    int n;  // # of child nodes
    int l, r;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int _val = 0, int _l = 0, int _r = 0, TreeNode *_left = NULL, TreeNode *_right = NULL) {
        this->val = _val;
        this->l = _l;
        this->r = _r;
        this->left = _left;
        this->right = _right;
    }
};

TreeNode *buildTree(vi &input, int left, int right) {
    if (left == right) {
        TreeNode *root = new TreeNode(input[left], left, right);
        return root;
    }
    int mid = (right - left) / 2 + left;
    TreeNode *root = new TreeNode(0, left, right);
    root->left = buildTree(input, left, mid);
    root->right = buildTree(input, mid + 1, right);
    root->val = root->left->val + root->right->val;
    return root;
}

void inorder(TreeNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->val << endl;
    inorder(root->right);
}

int findSum(TreeNode *root, int left, int right) {
    if (left > root->r || right < root->l) {
        cout << "이거 호출 되긴 함?" << endl;
        return 0;
    }
    if (left == root->l && right == root->r) return root->val;
    // if (left >= root->l && right <= root->r)
    int mid = (root->r - root->l) / 2 + root->l;
    if (right <= mid) {
        return findSum(root->left, left, right);
    } else if (left > mid) {
        return findSum(root->right, left, right);
    } else {
        int sum = 0;
        sum += findSum(root->left, left, mid);
        sum += findSum(root->right, mid + 1, right);
        return sum;
    }
}

TreeNode *update(TreeNode *root, int left, int right, int idx, int val) {
    if (root->l == idx && root->r == idx) {
        root->val = val;
        return root;
    }
    int mid = (right - left) / 2 + left;
    if (idx <= mid) {
        root->left = update(root->left, left, mid, idx, val);
        root->val = root->left->val + root->right->val;
    } else {
        root->right = update(root->right, mid + 1, right, idx, val);
        root->val = root->left->val + root->right->val;
    }
    return root;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, L, R;
    cin >> N >> L >> R;

    vi input(N);
    REP(i, 0, N) {
        cin >> input[i];
    }

    TreeNode *root = buildTree(input, 0, N - 1);
    // inorder(root);

    cout << findSum(root, L, R) << endl;

    // int ans = 0;
    // REP(i, L, R + 1) {
    //     ans += input[i];
    // }
    // cout << ans << endl;
    root = update(root, 0, N - 1, 1, 2);
    cout << findSum(root, L, R) << endl;
    return 0;
}
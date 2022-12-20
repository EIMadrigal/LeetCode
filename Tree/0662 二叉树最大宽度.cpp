/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int res = 0;
        queue<pair<TreeNode*, long long>> q;
        q.push({root, 0});
        while (!q.empty()) {
            long long curIndex = q.front().second;
            long long startIndex = curIndex;
            int curLevelSize = q.size();
            for (int i = 0; i < curLevelSize; ++i) {
                TreeNode* curNode = q.front().first;
                curIndex = q.front().second;
                q.pop();
                if (curNode->left) {
                    q.push({curNode->left, curIndex * 2 - startIndex});
                }
                if (curNode->right) {
                    q.push({curNode->right, curIndex * 2 + 1 - startIndex});
                }
            }
            res = max(res, static_cast<int>(curIndex - startIndex + 1));
        }
        return res;
    }
};

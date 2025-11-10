#include <iostream>
#include <queue>
#include <stack>

struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode() {}
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

int RecCountNodes(TreeNode* root)
{
    if(root) return RecCountNodes(root->left) + RecCountNodes(root->right) + 1;
    return 0;
}

int BfsCountNodes(TreeNode* root)
{
    if(!root) return 0;
    
    std::queue<TreeNode*> q;
    int count = 0;
    q.push(root);
    
    while(!q.empty())
    {
        TreeNode* curr = q.front();
        q.pop();
        count++;
        if(curr->left) q.push(curr->left);
        if(curr->right) q.push(curr->right);
    }
    return count;
}

int countHeight(TreeNode* root)
{
    if(root) return std::max(countHeight(root->left), countHeight(root->right)) + 1;
    return 0;
}

int countLeaves(TreeNode* root)
{
    if(!root) return 0;
    
    if(root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }
    
    return countLeaves(root->left) + countLeaves(root->right);
}

void preorder(TreeNode* root)
{
    if(root)
    {
        std::cout << root->data;
        preorder(root->left);
        preorder(root->right);
    }
    return;
}
void inorder(TreeNode* root)
{
    if(root)
    {
        preorder(root->left);
        std::cout << root->data;
        preorder(root->right);
    }
    return;
}
void postorder(TreeNode* root)
{
    if(root)
    {
        preorder(root->left);
        preorder(root->right);
        std::cout << root->data;
    }
    return;
}

void levelOrder(TreeNode* root)
{
    if(!root) return;
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    while(!q.empty())
    {
        std::cout << q.front()->data << ' ';
        
        if(q.front()->left) q.push(q.front()->left);
        if(q.front()->right) q.push(q.front()->right);
        
        q.pop();
    }
}

int NodeSum(TreeNode* root)
{
    if(!root) return 0;
    
    return NodeSum(root->left) + NodeSum(root->right) + root->data;
}

int findMax(TreeNode* root)
{
    if(!root) return 0;
    
    std::queue<TreeNode*> q;
    q.push(root);
    int max = root->data;
    
    while(!q.empty())
    {
        if(max <= q.front()->data) max = q.front()->data;
        
        if(q.front()->left) q.push(q.front()->left);
        if(q.front()->right) q.push(q.front()->right);
        
        q.pop();
    }
    return max;
}
int findMin(TreeNode* root)
{
    if(!root) return 0;
    
    std::queue<TreeNode*> q;
    q.push(root);
    int min = root->data;
    
    while(!q.empty())
    {
        if(min >= q.front()->data) min = q.front()->data;
        
        if(q.front()->left) q.push(q.front()->left);
        if(q.front()->right) q.push(q.front()->right);
        
        q.pop();
    }
    return min;
}

bool areIdentical(TreeNode* root1, TreeNode* root2)
{
    if(!root1 && !root2) return true;
    if(!root1 || !root2) return false;
    
    return (root1->data == root2->data) && areIdentical(root1->left, root2->left) && areIdentical(root1->right, root2->right);
}

int countNodesInDepth(TreeNode* root, int k)
{
    if(!root || k<= 0) return 0;
    
    if(k == 1) return 1;
    
    return countNodesInDepth(root->left, k-1) + countNodesInDepth(root->right, k-1);
}

void mirrorTree(TreeNode* root)
{
    if(!root) return;
    
    TreeNode* tmp = root->left;
    root->left == root->right;
    root->right = tmp;
    
    mirrorTree(root->left);
    mirrorTree(root->right);
}

int main()
{
    
    return 0;
}
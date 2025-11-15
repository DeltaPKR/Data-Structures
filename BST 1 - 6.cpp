#include <iostream>
#include <queue>
#include <stack>

struct TreeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int v):data(v), left(nullptr), right(nullptr) {}
};

TreeNode* Insert(TreeNode* root, int val)
{
    if(root==nullptr)
    {
        return new TreeNode(val);
    }
    
    if(root->data < val)
    {
        root->right = Insert(root->right, val);
    }
    else if(root->data > val)
    {
        root->left = Insert(root->left, val);
    }
    return root;
}
    
void PrintInode(TreeNode* root) 
{
    if(root == nullptr) 
    {
        return;
    }
    if(root->left) 
    {
        PrintInode(root->left);
    }
    std::cout << root->data << ' ';
    if(root->right) 
    {
        PrintInode(root->right);
    }
}
    
bool search(TreeNode* root, int val)
{
    if(!root) 
    {
        return false;
    }
    
    if(root->data == val) 
    {
        return true;
    }
    else if (val < root->data)
    {
        return search(root->left, val);
    }
    return search(root->right, val);
}

int findMinBST(TreeNode* root) 
{
    if (!root) { throw std::runtime_error("root is nullptr"); }
    if (root->left) 
    {
        return findMinBST(root->left);
    }
    return root->data;
}

int findMaxBST(TreeNode* root) 
{
    if (!root) { throw std::runtime_error("root is nullptr"); }
    if (root->right) 
    {
        return findMaxBST(root->right);
    }
    return root->data;
}

bool isValidBST(TreeNode* root) 
{
    if(!root) return true;
    
    bool right = true, left = true;
    if(root->left) 
    {
        int l_max = findMaxBST(root->left);
        if(root->data < l_max) 
        {
            return false;
        }
        left = isValidBST(root->left);
    } 
    if(root->right) 
    {
        int r_min = findMinBST(root->right);
        if( root->data > r_min) 
        {
            return false;
        }
        right = isValidBST(root->right);
    }
    
    if(right && left) 
    {
        return true;
    }
    return false;
}

int kthSmallest(TreeNode* root, int k)
{
    std::stack<TreeNode*> s;
    TreeNode* curr = root;
    
    while(curr != nullptr || !s.empty())
    {
        while(curr != nullptr)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        k--;
        
        if(k == 0) return curr->data;
        curr = curr->right;
    }
    throw std::out_of_range("k > nodes count");
}

TreeNode* buildBST(const std::vector<int> &nums, int left, int right)
{
    if(left > right) return nullptr;
    
    int mid = left + (right - left) / 2; //(left + right) / 2 бывало ошибки давало пришлось искать формулу нормальную
    TreeNode* node = new TreeNode(nums[mid]);
    
    node->left = buildBST(nums, left, mid - 1);
    node->right = buildBST(nums, mid + 1, right);
    
    return node;
}

TreeNode* sortedArrayToBST(const std::vector<int> &arr)
{
    if(arr.empty()) return nullptr;
    return buildBST(arr, 0, (int)arr.size() - 1);
}

int main()
{   
    return 0;
}
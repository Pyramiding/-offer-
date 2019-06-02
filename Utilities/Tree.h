//
// Created by W on 2019/3/13 0013.
//

#ifndef CODINGINTERVIEW_TREE_H
#define CODINGINTERVIEW_TREE_H

#include <vector>

struct TreeNode
{
    int                       m_nValue;
    std::vector<TreeNode*>    m_vChildren;
};

__declspec( dllexport ) TreeNode* CreateTreeNode(int value);
__declspec( dllexport ) void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild);
__declspec( dllexport ) void PrintTreeNode(const TreeNode* pNode);
__declspec( dllexport ) void PrintTree(const TreeNode* pRoot);
__declspec( dllexport ) void DestroyTree(TreeNode* pRoot);

#endif //CODINGINTERVIEW_TREE_H

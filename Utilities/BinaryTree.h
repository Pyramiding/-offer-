//
// Created by W on 2019/2/19 0019.
//

#ifndef CODINGINTERVIEW_BINARYTREE_H
#define CODINGINTERVIEW_BINARYTREE_H

struct BinaryTreeNode
{
    int                    m_nValue;
    BinaryTreeNode*        m_pLeft;
    BinaryTreeNode*        m_pRight;
    explicit BinaryTreeNode(int x = 0): m_nValue(x), m_pLeft(nullptr), m_pRight(nullptr) {}
};

__declspec( dllexport ) BinaryTreeNode* CreateBinaryTreeNode(int value);
__declspec( dllexport ) void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
__declspec( dllexport ) void PrintTreeNode(const BinaryTreeNode* pNode);
__declspec( dllexport ) void PrintTree(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void PrintTree_1(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void PrintTree_2(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void InOrderTraverse(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void InOrderTraverse_1(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void PostOrderTraverse(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void PostOrderTraverse_1(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void LevelOrderTraverse(const BinaryTreeNode* pRoot);
__declspec( dllexport ) void DestroyTree(BinaryTreeNode* pRoot);

#endif //CODINGINTERVIEW_BINARYTREE_H

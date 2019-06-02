//
// Created by W on 2019/2/19 0019.
//
#include <cstdio>
#include <vector>
#include <stack>
#include "BinaryTree.h"

using namespace std;

// 创建二叉树单节点
BinaryTreeNode* CreateBinaryTreeNode(int value)
{
    BinaryTreeNode* pNode = new BinaryTreeNode();
    pNode->m_nValue = value;
    pNode->m_pLeft = nullptr;
    pNode->m_pRight = nullptr;

    return pNode;
}

// 连接二叉树中某节点对应的左右子节点
void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
    if(pParent != nullptr)
    {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;
    }
}

// 打印二叉树某节点及其左右子节点的值
void PrintTreeNode(const BinaryTreeNode* pNode)
{
    if(pNode != nullptr)
    {
        printf("value of this node is: %d\n", pNode->m_nValue);

        if(pNode->m_pLeft != nullptr)
            printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
        else
            printf("left child is nullptr.\n");

        if(pNode->m_pRight != nullptr)
            printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
        else
            printf("right child is nullptr.\n");
    }
    else
    {
        printf("this node is nullptr.\n");
    }

    printf("\n");
}

//===============各种遍历算法时间复杂度和空间复杂度都为O(n)，n为二叉树高度====================
//前序遍历（递归） 根-左-右
//void PreOrderTraverse(const BinaryTreeNode* pRoot)
void PrintTree(const BinaryTreeNode* pRoot)
{
    PrintTreeNode(pRoot);

    if(pRoot != nullptr)
    {
        if(pRoot->m_pLeft != nullptr)
            PrintTree(pRoot->m_pLeft);

        if(pRoot->m_pRight != nullptr)
            PrintTree(pRoot->m_pRight);
    }
}

//前序遍历（非递归） 根-左-右
//层序压栈
void PrintTree_1(const BinaryTreeNode* pRoot)
{
    if (pRoot != nullptr)
    {
        stack<const BinaryTreeNode*> stacks;
        const BinaryTreeNode* node;

        stacks.push(pRoot);
        while (!stacks.empty())
        {
            node = stacks.top();
            stacks.pop();
            PrintTreeNode(node);

            if (node->m_pRight != nullptr)
                stacks.push(node->m_pRight);

            if (node->m_pLeft != nullptr)
                stacks.push(node->m_pLeft);
        }
    }
}

//左斜子树压栈
void PrintTree_2(const BinaryTreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        vector<const BinaryTreeNode*> Nodes; //定义一个容器,存储节点
        const BinaryTreeNode* node = pRoot;

        while(node != nullptr || !Nodes.empty())
        {                                    //从树根开始一直输出左节点
            while(node != nullptr)
            {
                PrintTreeNode(node);
                Nodes.push_back(node);       //将输出的节点加入栈中
                node = node->m_pLeft;
            }

            node = Nodes.back();  //该节点不存在左节点时,该节点出栈,搜索该节点右节点
            Nodes.pop_back();

            node = node->m_pRight;
        }
    }
}

//中序遍历（递归） 左-根-右
void InOrderTraverse(const BinaryTreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        if(pRoot->m_pLeft != nullptr)
            InOrderTraverse(pRoot->m_pLeft);

        PrintTreeNode(pRoot);

        if(pRoot->m_pRight != nullptr)
            InOrderTraverse(pRoot->m_pRight);
    }
}

//中序遍历（非递归） 左-根-右
void InOrderTraverse_1(const BinaryTreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        vector<const BinaryTreeNode*> Nodes; //定义一个容器,存储节点
        const BinaryTreeNode* node = pRoot;

        while(node != nullptr || !Nodes.empty())
        {                                    //一直查找树的左节点,一直进栈
            while(node != nullptr)
            {
                Nodes.push_back(node);       //将输出的节点加入栈中
                node = node->m_pLeft;
            }

            node = Nodes.back();  //该节点不存在左节点时,该节点出栈,搜索该节点右节点
            Nodes.pop_back();
            PrintTreeNode(node);

            node = node->m_pRight;
        }
    }
}

//后序遍历（递归） 左-右-根
void PostOrderTraverse(const BinaryTreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        if(pRoot->m_pLeft != nullptr)
            PostOrderTraverse(pRoot->m_pLeft);

        if(pRoot->m_pRight != nullptr)
            PostOrderTraverse(pRoot->m_pRight);

        PrintTreeNode(pRoot);
    }
}

//后序遍历（非递归） 左-右-根
void PostOrderTraverse_1(const BinaryTreeNode* pRoot)
{
	if(pRoot == nullptr)
		return;

    vector<const BinaryTreeNode*> Nodes1, Nodes2; //定义一个容器,存储节点
    const BinaryTreeNode* node = pRoot;
    Nodes1.push_back(node);

    while(!Nodes1.empty())
    {    //该节点出栈1,左右节点进栈1(对于左右节点,右节点先出栈1,也先进栈2)
        node = Nodes1.back();
        Nodes1.pop_back();

        if(node->m_pLeft != nullptr)
            Nodes1.push_back(node->m_pLeft);
        if(node->m_pRight != nullptr)
            Nodes1.push_back(node->m_pRight);

        Nodes2.push_back(node); //该节点进栈2
    }
    // 最终辅助栈2为倒序的后序遍历
    while(!Nodes2.empty())
    {
        node = Nodes2.back();
        Nodes2.pop_back();
        PrintTreeNode(node);
    }
	/* 也可以Nodes2存储节点值，更省空间
	Nodes2.push_back(node->m_nValue);
	reverse(Nodes2.begin(), Nodes2.end());
	for(auto elmt: Nodes2)
		printf("%d, ", elmt);
	*/
}

void levelTraverse(const BinaryTreeNode* pRoot,
        int level, vector<vector<const BinaryTreeNode*> >& res)
        //注意此处不用用int& level,否则levelTraverse(pRoot->m_pLeft, level++, res)报错
        //不能将非常量左值引用绑定到右值，这里传入参数level++为右值
{
    if(pRoot)
    {
        if(res.size() < level + 1) //若当前子容器数小于层数
        {
            vector<const BinaryTreeNode*> temp;
            res.push_back(temp);
        }

        res[level].push_back(pRoot);

        levelTraverse(pRoot->m_pLeft, level+1, res);
        levelTraverse(pRoot->m_pRight, level+1, res);
    }
}

//层序遍历（递归）
void LevelOrderTraverse(const BinaryTreeNode* pRoot)
{
    vector<vector<const BinaryTreeNode*> > res; //双重向量，每层节点一个向量
    int level = 0;
    levelTraverse(pRoot, level, res);

    for(auto sub_vector: res)
        for(auto elmt: sub_vector)
            PrintTreeNode(elmt);
}

//层序遍历（非递归）
//习题32-1

// 销毁二叉树（释放内存，释放指针）
void DestroyTree(BinaryTreeNode* pRoot)
{
    if(pRoot != nullptr)
    {
        BinaryTreeNode* pLeft = pRoot->m_pLeft;
        BinaryTreeNode* pRight = pRoot->m_pRight;

        delete pRoot;
        pRoot = nullptr;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}

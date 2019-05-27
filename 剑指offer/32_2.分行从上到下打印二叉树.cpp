//
// Created by W on 2019/2/27 0027.
//

// 面试题32（二）：分行从上到下打印二叉树
// 题目：从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层
// 打印到一行。
#include <iostream>
#include <cstdio>
#include <queue>
#include <deque>
#include "Utilities\BinaryTree.h"

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    vector<vector<int>> Print(BinaryTreeNode* pRoot)
    {
        vector<vector<int>> result;
        if(!pRoot)
            return result;

        deque<TreeNode*> curNode = {pRoot};
        deque<TreeNode*> nextNode;
        vector<int> temp;

        while(!curNode.empty() || !nextNode.empty())
        {
            TreeNode *pNode = curNode.front();
            curNode.pop_front();
            temp.push_back(pNode->val);

            if (pNode->left)
                nextNode.push_back(pNode->left);
            if (pNode->right)
                nextNode.push_back(pNode->right);

            if (curNode.empty())
            {
                result.push_back(temp);
                temp = {};
                curNode = nextNode;
                nextNode = {};
            }
        }
        return result;
    }

private:

};

// 我的算法
void Print_my(BinaryTreeNode* pRoot)
{
    deque<BinaryTreeNode*> curNode = {pRoot};
    queue<BinaryTreeNode*> nextNode;

    while(!curNode.empty() || !nextNode.empty())
    {
        BinaryTreeNode* pNode = curNode.front();
        curNode.pop_front();
        printf("%d", pNode->m_nValue);

        if(pNode->m_pLeft)
            nextNode.push_back(pNode->m_pLeft);
        if(pNode->m_pRight)
            nextNode.push_back(pNode->m_pRight);

        if(curNode.empty())
        {
            curNode = nextNode;
            nextNode = {};
        }
    }
}

void Print(BinaryTreeNode* pRoot)
{
    if(pRoot == nullptr)
        return;

    std::queue<BinaryTreeNode*> nodes;
    nodes.push(pRoot);
    int nextLevel = 0;
    int toBePrinted = 1;
    while(!nodes.empty())
    {
        BinaryTreeNode* pNode = nodes.front();
        printf("%d ", pNode->m_nValue);

        if(pNode->m_pLeft)
        {
            nodes.push(pNode->m_pLeft);
            ++nextLevel;
        }
        if(pNode->m_pRight)
        {
            nodes.push(pNode->m_pRight);
            ++nextLevel;
        }

        nodes.pop();
        --toBePrinted;
        if(toBePrinted == 0)
        {
            printf("\n");
            toBePrinted = nextLevel;
            nextLevel = 0;
        }
    }
}

// ====================测试代码====================
//            8
//        6      10
//       5 7    9  11
void Test1()
{
    BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
    BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
    BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
    BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

    ConnectTreeNodes(pNode8, pNode6, pNode10);
    ConnectTreeNodes(pNode6, pNode5, pNode7);
    ConnectTreeNodes(pNode10, pNode9, pNode11);

    printf("====Test1 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("8 \n");
    printf("6 10 \n");
    printf("5 7 9 11 \n\n");

    printf("Actual Result is: \n");
    Print(pNode8);
    printf("\n");

    DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test2()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);

    printf("====Test2 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("5 \n");
    printf("4 \n");
    printf("3 \n");
    printf("2 \n\n");

    printf("Actual Result is: \n");
    Print(pNode5);
    printf("\n");

    DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
void Test3()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

    ConnectTreeNodes(pNode5, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode2);

    printf("====Test3 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("5 \n");
    printf("4 \n");
    printf("3 \n");
    printf("2 \n\n");

    printf("Actual Result is: \n");
    Print(pNode5);
    printf("\n");

    DestroyTree(pNode5);
}

void Test4()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    printf("====Test4 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("5 \n\n");

    printf("Actual Result is: \n");
    Print(pNode5);
    printf("\n");

    DestroyTree(pNode5);
}

void Test5()
{
    printf("====Test5 Begins: ====\n");
    printf("Expected Result is:\n");

    printf("Actual Result is: \n");
    Print(nullptr);
    printf("\n");
}

//        100
//        /
//       50
//         \
//         150
void Test6()
{
    BinaryTreeNode* pNode100 = CreateBinaryTreeNode(100);
    BinaryTreeNode* pNode50 = CreateBinaryTreeNode(50);
    BinaryTreeNode* pNode150 = CreateBinaryTreeNode(150);

    ConnectTreeNodes(pNode100, pNode50, nullptr);
    ConnectTreeNodes(pNode50, nullptr, pNode150);

    printf("====Test6 Begins: ====\n");
    printf("Expected Result is:\n");
    printf("100 \n");
    printf("50 \n");
    printf("150 \n\n");

    printf("Actual Result is: \n");
    Print(pNode100);
    printf("\n");
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
}

int main(int argc, char* argv[])
{
    manytest();

    return 0;
}

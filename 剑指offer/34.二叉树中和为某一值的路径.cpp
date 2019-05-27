//
// Created by W on 2019/2/28 0028.
//
// 面试题34：二叉树中和为某一值的路径
// 题目：输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所
// 有路径。从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

#include <iostream>
#include <cstdio>
#include <vector>

#include "Utilities\BinaryTree.h"

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    vector<vector<int> > FindPath(BinaryTreeNode* root, int expectNumber)
    {
        vector<vector<int> > paths;
        if(root == nullptr)
            return paths;

        vector<int> curPath;
        int currentSum = 0;
        dfs(root, expectNumber, curPath, currentSum, paths);
        return paths;
    }

    void dfs(BinaryTreeNode* pNode, int expectedSum, vector<int>& curPath,
             int& currentSum, vector<vector<int> >& paths)
    {
        currentSum += pNode->m_nValue;
        curPath.push_back(pNode->m_nValue);

        bool isLeaf = !pNode->m_pLeft && !pNode->m_pRight;
        if(currentSum == expectedSum && isLeaf)
            paths.push_back(curPath);

        if(pNode->m_pLeft != nullptr)
            dfs(pNode->m_pLeft, expectedSum, curPath, currentSum, paths);
        if(pNode->m_pRight != nullptr)
            dfs(pNode->m_pRight, expectedSum, curPath, currentSum, paths);

        currentSum -= pNode->m_nValue;
        curPath.pop_back();
    }

private:

};

void dfs(BinaryTreeNode* pNode, int expectedSum, vector<int>& path, int& currentSum)
{
    currentSum += pNode->m_nValue;
    path.push_back(pNode->m_nValue);

    bool isLeaf = !pNode->m_pLeft && !pNode->m_pRight;
    if(currentSum == expectedSum && isLeaf)
    {
        printf("A path is found: ");
        for(auto elmt: path)
            printf("%d\t", elmt);
        printf("\n");
    }

    if(pNode->m_pLeft != nullptr)
        dfs(pNode->m_pLeft, expectedSum, path, currentSum);
    if(pNode->m_pRight != nullptr)
        dfs(pNode->m_pRight, expectedSum, path, currentSum);

    currentSum -= pNode->m_nValue;
    path.pop_back();
}

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
    if(pRoot == nullptr)
        return;

    vector<int> path;
    int currentSum = 0;
    dfs(pRoot, expectedSum, path, currentSum);
}


// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot, int expectedSum)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    FindPath(pRoot, expectedSum);

    printf("\n");
}

//            10
//         /      \
//        5        12
//       /\
//      4  7
// 有两条路径上的结点和为22
void Test1()
{
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNode10, pNode5, pNode12);
    ConnectTreeNodes(pNode5, pNode4, pNode7);

    printf("Two paths should be found in Test1.\n");
    Test("Test1", pNode10, 22);

    DestroyTree(pNode10);
}

//            10
//         /      \
//        5        12
//       /\
//      4  7
// 没有路径上的结点和为15
void Test2()
{
    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNode10, pNode5, pNode12);
    ConnectTreeNodes(pNode5, pNode4, pNode7);

    printf("No paths should be found in Test2.\n");
    Test("Test2", pNode10, 15);

    DestroyTree(pNode10);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
// 有一条路径上面的结点和为15
void Test3()
{
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

    ConnectTreeNodes(pNode5, pNode4, nullptr);
    ConnectTreeNodes(pNode4, pNode3, nullptr);
    ConnectTreeNodes(pNode3, pNode2, nullptr);
    ConnectTreeNodes(pNode2, pNode1, nullptr);

    printf("One path should be found in Test3.\n");
    Test("Test3", pNode5, 15);

    DestroyTree(pNode5);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
// 没有路径上面的结点和为16
void Test4()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
    BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

    ConnectTreeNodes(pNode1, nullptr, pNode2);
    ConnectTreeNodes(pNode2, nullptr, pNode3);
    ConnectTreeNodes(pNode3, nullptr, pNode4);
    ConnectTreeNodes(pNode4, nullptr, pNode5);

    printf("No paths should be found in Test4.\n");
    Test("Test4", pNode1, 16);

    DestroyTree(pNode1);
}

// 树中只有1个结点
void Test5()
{
    BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

    printf("One path should be found in Test5.\n");
    Test("Test5", pNode1, 1);

    DestroyTree(pNode1);
}

// 树中没有结点
void Test6()
{
    printf("No paths should be found in Test6.\n");
    Test("Test6", nullptr, 0);
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
    //manytest();

    BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
    BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
    BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNode10, pNode5, pNode12);
    ConnectTreeNodes(pNode5, pNode4, pNode7);

    vector<int> push = {5, 7, 6, 9, 11, 10, 8};
    Solution solver;
    vector<vector<int> > ret = solver.FindPath(pNode10, 22);
    for(auto elmt1: ret)
    {
        for(auto elmt2: elmt1)
            cout << elmt2 << " ";
        cout << endl;
    }

    //cout << boolalpha << ret << endl;

    return 0;
}

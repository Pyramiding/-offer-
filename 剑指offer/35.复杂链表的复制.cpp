//
// Created by W on 2019/3/1 0001.
//
// 面试题35：复杂链表的复制
// 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，复
// 制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个
// 结点外，还有一个m_pSibling 指向链表中的任意结点或者nullptr。

#include <iostream>
#include <cstdio>
#include <hash_map>

using namespace std;

//
// NowCoder提交格式
//

// 复杂链表定义
//========================================================================
struct ComplexListNode
{
    int                 m_nValue;
    ComplexListNode*    m_pNext;
    ComplexListNode*    m_pSibling;
};

ComplexListNode* CreateNode(int nValue)
{
    auto pNode = new ComplexListNode();
    pNode->m_nValue = nValue;
    pNode->m_pNext = nullptr;
    pNode->m_pSibling = nullptr;
    return pNode;
}

void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling)
{
    if(pNode)
    {
        pNode->m_pNext = pNext;
        pNode->m_pSibling = pSibling;
    }
}

void PrintList(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode)
    {
        printf("The value of this node is: %d.\n", pNode->m_nValue);
        if(pNode->m_pSibling)
            printf("The value of its sibling is: %d.\n", pNode->m_pSibling->m_nValue);
        else
            printf("This node does not have a sibling.\n");
        printf("\n");

        pNode = pNode->m_pNext;
    }
}

//=============================方法一======================================
// 复制原始链表的节点n并创建新的节点n'，并连接在n后面
void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode)
    {
        auto pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = nullptr;

        pNode->m_pNext = pCloned;

        pNode = pCloned->m_pNext;
    }
}

// 根据n的随机指针指向的节点s，确定n'的随机指针指向的节点s'，s'即为s的下一节点
void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode)
    {
        ComplexListNode* pCloned = pNode->m_pNext;
        if(pNode->m_pSibling != nullptr)
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;

        pNode = pCloned->m_pNext;
    }
}

// 把链表拆分开，奇数位置节点组成原始链表，偶数位置节点组成复制后的链表
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = nullptr;
    ComplexListNode* pClonedNode = nullptr;

    if(pNode)
    {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }

    while(pNode)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;

        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }

    return pClonedHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

//=============================方法二======================================
//使用哈希表，以空间换时间
ComplexListNode* Clone1(ComplexListNode* pHead)
{
    // 创建哈希表，原节点和复制节点对应
    map<ComplexListNode*, ComplexListNode*> maps;
    ComplexListNode* cur = pHead;
    while (cur != nullptr) {
        maps.insert({cur, CreateNode(cur->m_nValue)});
        cur = cur->m_pNext;
    }

    // 根据键-值对应关系连接赋值节点间的联系
    cur = pHead;
    while (cur != nullptr) {
        maps[cur]->m_pNext = maps[cur->m_pNext];
        maps[cur]->m_pSibling = maps[cur->m_pSibling];
        cur = cur->m_pNext;
    }
    return maps[pHead];
}

// ====================测试代码====================
void Test(const char* testName, ComplexListNode* pHead)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The original list is:\n");
    PrintList(pHead);

    ComplexListNode* pClonedHead = Clone(pHead);

    printf("The cloned list is:\n");
    PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, pNode3);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, pNode3);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode4);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
    ComplexListNode* pNode1 = CreateNode(1);
    BuildNodes(pNode1, nullptr, pNode1);

    Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
    Test("Test5", nullptr);
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
}


int main(int argc, char* argv[])
{
    manytest();

/*    vector<int> push = {5, 7, 6, 9, 11, 10, 8};
    Solution solver;
    vector<vector<int> > ret = solver.FindPath(pNode10, 22);
    for(auto elmt1: ret)
    {
        for(auto elmt2: elmt1)
            cout << elmt2 << " ";
        cout << endl;
    }*/

    //cout << boolalpha << ret << endl;

    return 0;
}
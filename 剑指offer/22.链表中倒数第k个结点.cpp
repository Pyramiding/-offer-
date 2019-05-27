//
// Created by W on 2019/2/24 0024.
//
// 面试题22：链表中倒数第k个结点
// 题目：输入一个链表，输出该链表中倒数第k个结点。为了符合大多数人的习惯，
// 本题从1开始计数，即链表的尾结点是倒数第1个结点。例如一个链表有6个结点，
// 从头结点开始它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个结点是
// 值为4的结点。

#include <iostream>
#include <cstdio>
#include "Utilities\List.h"

using namespace std;

//
// NowCoder提交格式
//

class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    }

private:
};

//链表中倒数第k个结点
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
    if(pListHead == nullptr || k == 0)
        return nullptr;

    ListNode* pAhead = pListHead;
    ListNode* pBehind = nullptr;

    for(int i = 0; i < k - 1; i++)
    {
        if(pAhead->m_pNext != nullptr)
            pAhead = pAhead->m_pNext;
        else
            return nullptr;
    }

    pBehind = pListHead;
    while(pAhead->m_pNext != nullptr)
    {
        pAhead = pAhead->m_pNext;
        pBehind = pBehind->m_pNext;
    }

    return pBehind;
}

//链表中间节点
ListNode* FindMid(ListNode* pListHead)
{
    if(pListHead == nullptr)
        return nullptr;

    if(pListHead->m_pNext == nullptr || pListHead->m_pNext->m_pNext == nullptr)
        return pListHead;

    ListNode* pFast = pListHead;
    ListNode* pLow = pListHead;

    while(pFast != nullptr && pFast->m_pNext != nullptr){
        pFast = pFast->m_pNext->m_pNext;
        pLow = pLow->m_pNext;
    }

    return pLow;
}

// ====================测试代码====================
// 测试要找的结点在链表中间
void Test1()
{
    printf("\n=====Test1 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 4.\n");
    ListNode* pNode_k = FindKthToTail(pNode1, 2);
    PrintListNode(pNode_k);

    printf("expected result: 3.\n");
    ListNode* pNode_mid = FindMid(pNode1);
    PrintListNode(pNode_mid);

    DestroyList(pNode1);
}

// 测试要找的结点是链表的尾结点
void Test2()
{
    printf("\n=====Test2 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 5.\n");
    ListNode* pNode = FindKthToTail(pNode1, 1);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试要找的结点是链表的头结点
void Test3()
{
    printf("=====Test3 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 1.\n");
    ListNode* pNode = FindKthToTail(pNode1, 5);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试空链表
void Test4()
{
    printf("=====Test4 starts:=====\n");
    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(nullptr, 100);
    PrintListNode(pNode);
}

// 测试输入的第二个参数大于链表的结点总数
void Test5()
{
    printf("=====Test5 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(pNode1, 6);
    PrintListNode(pNode);

    DestroyList(pNode1);
}

// 测试输入的第二个参数为0
void Test6()
{
    printf("=====Test6 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(pNode1, 0);
    PrintListNode(pNode);

    DestroyList(pNode1);
}


int main(int argc, char* argv[])
{
    Test1();
/*    Test2();
    Test3();
    Test4();
    Test5();
    Test6();*/

/*    Solution solver;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int result = 0;
    //solver.reOrderArray(arr);
    for(auto elmt : arr)
        cout << elmt << ' ';
    cout << endl;
    cout << result << endl;*/

    return 0;
}

//
// Created by W on 2019/2/24 0024.
//
// 面试题24：反转链表
// 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的
// 头结点。
#include <iostream>
#include <cstdio>

#include "Utilities\List.h"

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead)
    {
        ListNode* pReversedHead = nullptr;//当前指针
        ListNode* pNode = pHead;//新链表的头指针
        ListNode* pPrev = nullptr;//当前指针的前一个结点
        while(pNode != nullptr)
        {
            ListNode* pNext = pNode->m_pNext;//链断开之前一定要保存断开位置后边的结点
            if(pNext == nullptr)
                pReversedHead = pNode;//当pNext为空时，说明当前结点为尾节点

            pNode->m_pNext = pPrev;//指针反转

            pPrev = pNode;
            pNode = pNext;
        }
        return pReversedHead;
    }

private:
};

//循环方法
ListNode* ReverseList1(ListNode* pHead)
{
    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;
    while(pNode != nullptr)
    {
        ListNode* pNext = pNode->m_pNext; //断开连接

        if(pNext == nullptr)
            pReversedHead = pNode;

        pNode->m_pNext = pPrev;

        pPrev = pNode; // 右移
        pNode = pNext;
    } //这里可以不用pReversedHead变量，返回pPrev即可

    return pReversedHead;
}

//循环方法简写
ListNode* ReverseList1(ListNode* pHead)
{
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;
    while(pNode != nullptr)
    {
        ListNode* pNext = pNode->m_pNext; //断开连接
        pNode->m_pNext = pPrev;
        pPrev = pNode; // 右移
        pNode = pNext;
    }

    return pPrev;
}


//递归方法
ListNode* ReverseList(ListNode* pHead)
{
    if(pHead == nullptr || pHead->m_pNext == nullptr)
        return pHead;
    ListNode* pNext = pHead->m_pNext;
    pHead->m_pNext = nullptr;
    ListNode* newHead = ReverseList(pNext);
    pNext->m_pNext = pHead;
    return newHead;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
    printf("The original list is: \n");
    PrintList(pHead);

    ListNode* pReversedHead = ReverseList(pHead);

    printf("The reversed list is: \n");
    PrintList(pReversedHead);

    return pReversedHead;
}

// 输入的链表有多个结点
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
    Test(nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    Solution solver;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int result = 0;
    //solver.reOrderArray(arr);
    for(auto elmt : arr)
        cout << elmt << ' ';
    cout << endl;
    cout << result << endl;

    return 0;
}
//
// Created by W on 2019/2/18 0018.
//
// 面试题6：从尾到头打印链表
// 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。

#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include "Utilities\List.h"
using namespace std;


//
// NowCoder提交格式
//

class Solution {
public:
    // 递归
    vector<int> printListFromTailToHead1(ListNode* head) {
        vector<int> dev;
        if (head != nullptr) {
            if (head->m_pNext != nullptr) {
                dev = printListFromTailToHead1(head->m_pNext);
            }
            dev.push_back(head->m_nValue);
        }
        return dev;
    }
    // 堆栈
    vector<int> printListFromTailToHead2(ListNode* head) {
        stack<ListNode*> nodes;
        vector<int> dev;
        ListNode *pNode = head;
        while(pNode != nullptr) {
            nodes.push(pNode);
            pNode = pNode->m_pNext;
        }

        while(!nodes.empty()) {
            pNode = nodes.top();
            dev.push_back(pNode->m_nValue);
            nodes.pop();
        }
        return dev;
    }

};

// 堆栈
void PrintListReversingly_Iteratively(ListNode* pHead)
{
    stack<ListNode*> nodes;

    ListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        nodes.push(pNode);
        pNode = pNode->m_pNext;
    }

    while(!nodes.empty())
    {
        pNode = nodes.top();
        printf("%d\t", pNode->m_nValue);
        nodes.pop();
    }
}

// 递归
void PrintListReversingly_Recursively(ListNode* pHead)
{
    if(pHead != nullptr)
    {
        if (pHead->m_pNext != nullptr)
        {
            PrintListReversingly_Recursively(pHead->m_pNext);
        }
        printf("%d\t", pHead->m_nValue);
    }
}

// ====================测试代码====================
void Test(ListNode* pHead)
{
    PrintList(pHead);
    PrintListReversingly_Iteratively(pHead);
    printf("\n");
    PrintListReversingly_Recursively(pHead);
}

// 1->2->3->4->5
void Test1()
{
    printf("\nTest1 begins.\n");

    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test(pNode1);

    DestroyList(pNode1);
}

// 只有一个结点的链表: 1
void Test2()
{
    printf("\nTest2 begins.\n");

    ListNode* pNode1 = CreateListNode(1);

    Test(pNode1);

    DestroyList(pNode1);
}

// 空链表
void Test3()
{
    printf("\nTest3 begins.\n");

    Test(nullptr);
}


int main(int argc, char* argv[])
{
/*    Test1();
    Test2();
    Test3();*/

    // 剑指offer方式创建链表
    Solution solver;
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);

    vector<int> values1;
    values = solver.printListFromTailToHead2(pNode1);
    for (auto elmt: values1)
        cout << elmt << ' ';
    cout << endl;

    // NowCoder和Leetcode方式创建链表
    ListNode node1 = ListNode(1);
    ListNode node2 = ListNode(2);
    node1.m_pNext = &node2;

    vector<int> values2;
    values = solver.printListFromTailToHead2(&node1);
    for (auto elmt: values2)
        cout << elmt << ' ';
    cout << endl;

    return 0;
}


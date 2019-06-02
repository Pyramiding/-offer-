//
// Created by W on 2019/2/18 0018.
//

#ifndef CODINGINTERVIEW_LIST_H
#define CODINGINTERVIEW_LIST_H

struct ListNode
{
    int       m_nValue;
    ListNode* m_pNext;
    explicit ListNode(int x = 0): m_nValue(x), m_pNext(nullptr){}
};

// 声明一个导出函数，是说这个函数要从本DLL导出。我要给别人用。一般用于dll中
__declspec( dllexport ) ListNode* CreateListNode(int value);
__declspec( dllexport ) void ConnectListNodes(ListNode* pCurrent, ListNode* pNext);
__declspec( dllexport ) void PrintListNode(ListNode* pNode);
__declspec( dllexport ) void PrintList(ListNode* pHead);
__declspec( dllexport ) void DestroyList(ListNode* pHead);
__declspec( dllexport ) void AddToTail(ListNode** pHead, int value);
__declspec( dllexport ) void RemoveNode(ListNode** pHead, int value);

#endif //CODINGINTERVIEW_LIST_H

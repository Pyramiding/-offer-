//
// Created by W on 2019/2/26 0026.
//
// 面试题31：栈的压入、弹出序列
// 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
// 否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、
// 5是某栈的压栈序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，但
// 4、3、5、1、2就不可能是该压栈序列的弹出序列。

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    bool IsPopOrder1(vector<int> pushV, vector<int> popV)
    {
        bool bPossible = false;
        if(!pushV.empty() && !popV.empty())
        {
            auto itPush = pushV.begin();
            auto itPop = popV.begin();

            stack<int> stackData;

            while(itPop < popV.end())
            {
                while(stackData.empty() || stackData.top() != *itPop)
                {
                    if(itPush == pushV.end())
                        break;
                    stackData.push(*itPush);
                    itPush++;
                }

                if(stackData.top() != *itPop)
                    break;

                stackData.pop();
                itPop++;
            }
            if(stackData.empty() && itPop == popV.end())
                bPossible = true;
        }
        return bPossible;
    }

    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        if(pushV.empty())
            return false;

        vector<int> stack;
        for(int i = 0, j = 0; i < pushV.size(); i++)
        {
            stack.push_back(pushV[i]);

            while(j < popV.size() && stack.back() == popV[j])
            {
                stack.pop_back();
                j++;
            }
        }
        return stack.empty();
    }

private:

};

bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;

    if(pPush != nullptr && pPop != nullptr && nLength > 0)
    {
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;

        //辅助栈
        stack<int> stackData;

        while(pNextPop - pPop < nLength)
        {
            // 当辅助栈的栈顶元素不是要弹出的元素
            // 先压入一些数字入栈
            while(stackData.empty() || stackData.top() != *pNextPop)
            {
                // 如果所有数字都压入辅助栈了，退出循环
                if(pNextPush - pPush == nLength)
                    break;

                stackData.push(*pNextPush);

                pNextPush ++;
            }

            if(stackData.top() != *pNextPop)
                break;

            stackData.pop();
            pNextPop++;
        }

        if(stackData.empty() && pNextPop - pPop == nLength)
            bPossible = true;
    }

    return bPossible;
}

// ====================测试代码====================
void Test(const char* testName, const int* pPush, const int* pPop, int nLength, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(IsPopOrder(pPush, pPop, nLength) == expected)
        printf("Passed.\n");
    else
        printf("failed.\n");
}

void Test1()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {4, 5, 3, 2, 1};

    Test("Test1", push, pop, nLength, true);
}

void Test2()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {3, 5, 4, 2, 1};

    Test("Test2", push, pop, nLength, true);
}

void Test3()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {4, 3, 5, 1, 2};

    Test("Test3", push, pop, nLength, false);
}

void Test4()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {3, 5, 4, 1, 2};

    Test("Test4", push, pop, nLength, false);
}

// push和pop序列只有一个数字
void Test5()
{
    const int nLength = 1;
    int push[nLength] = {1};
    int pop[nLength] = {2};

    Test("Test5", push, pop, nLength, false);
}

void Test6()
{
    const int nLength = 1;
    int push[nLength] = {1};
    int pop[nLength] = {1};

    Test("Test6", push, pop, nLength, true);
}

void Test7()
{
    Test("Test7", nullptr, nullptr, 0, false);
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
}

int main(int argc, char* argv[])
{
    manytest();

    vector<int> push = {1, 2, 3, 4, 5};
    vector<int> pop = {4, 5, 3, 2, 1};
    Solution solver;
    bool ret = solver.IsPopOrder(push, pop);
    cout << boolalpha << ret << endl;

    return 0;
}
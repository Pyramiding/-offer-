//
// Created by W on 2019/3/3 0003.
//

// 面试题42：连续子数组的最大和
// 题目：输入一个整型数组，数组里有正数也有负数。数组中一个或连续的多个整
// 数组成一个子数组。求所有子数组的和的最大值。要求时间复杂度为O(n)。

#include <iostream>
#include <cstdio>

using namespace std;

//
// NowCoder提交格式
//

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        if(array.empty())
            return 0;

        int curSum = 0, greatestSum = 0x80000000;
        for(auto elmt: array)
        {
            if(curSum <= 0)
                curSum = elmt;
            else
                curSum += elmt;

            if(curSum > greatestSum)
                greatestSum = curSum;
        }

        return greatestSum;
    }

private:
};

bool g_InvalidInput = false;

int FindGreatestSumOfSubArray(const int *pData, int nLength)
{
    if(!pData || nLength <= 0)
    {
        g_InvalidInput = true;
        return 0;
    }

    int nCurSum = 0, nGreatestSum = 0x80000000;
    for(int i = 0; i < nLength; ++i)
    {
        if(nCurSum <= 0)
            nCurSum = pData[i];
        else
            nCurSum += pData[i];

        if(nCurSum > nGreatestSum)
            nGreatestSum = nCurSum;
    }
    return nGreatestSum;
}

// ====================测试代码====================
void Test(const char* testName, int* pData, int nLength, int expected, bool expectedFlag)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    int result = FindGreatestSumOfSubArray(pData, nLength);
    if(result == expected && expectedFlag == g_InvalidInput)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

// 1, -2, 3, 10, -4, 7, 2, -5
void Test1()
{
    int data[] = {1, -2, 3, 10, -4, 7, 2, -5};
    Test("Test1", data, sizeof(data) / sizeof(int), 18, false);
}

// 所有数字都是负数
// -2, -8, -1, -5, -9
void Test2()
{
    int data[] = {-2, -8, -1, -5, -9};
    Test("Test2", data, sizeof(data) / sizeof(int), -1, false);
}

// 所有数字都是正数
// 2, 8, 1, 5, 9
void Test3()
{
    int data[] = {2, 8, 1, 5, 9};
    Test("Test3", data, sizeof(data) / sizeof(int), 25, false);
}

// 无效输入
void Test4()
{
    Test("Test4", nullptr, 0, 0, true);
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
}

int main(int argc, char* argv[]) {
    //manytest();

    vector<int> push = {1, -2, 3, 10, -4, 7, 2, -5};
    Solution solver;
    int res = solver.FindGreatestSumOfSubArray(push);
    cout << res << "  ";

    //cout << boolalpha << ret << endl;
    return 0;
}


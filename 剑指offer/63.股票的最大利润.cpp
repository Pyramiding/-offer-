//
// Created by W on 2019/3/11 0011.
//
// 面试题63：股票的最大利润
// 题目：假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖交易该股
// 票可能获得的利润是多少？例如一只股票在某些时间节点的价格为{9, 11, 8, 5,
// 7, 12, 16, 14}。如果我们能在价格为5的时候买入并在价格为16时卖出，则能
// 收获最大的利润11。

#include <iostream>
#include <cstdio>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
private:
};

int MaxDiff1(const int* numbers, unsigned length)
{
    if(!numbers || length < 2)
        return 0;

    int min = numbers[0];
    int maxDiff = numbers[1] - min;

    for(int i = 2; i < length; ++i)
    {
        if(numbers[i - 1] < min)
            min = numbers[i - 1];

        int currentDiff = numbers[i] - min;
        if(currentDiff > maxDiff)
            maxDiff = currentDiff;
    }
    return maxDiff;
}

int MaxDiff(const int* numbers, unsigned length)
{
    if(!numbers || length < 2)
        return 0;
    int soFarMin = numbers[0];
    int maxProfit = 0;
    for(int i = 1; i < length; ++i)
    {
        soFarMin = min(soFarMin, numbers[i]);
        maxProfit = max(maxProfit, numbers[i] - soFarMin);
    }
    printf("%d, ", maxProfit);
    return maxProfit;
}

// ====================测试代码====================
void Test(const char* testName, const int* numbers, unsigned int length, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(MaxDiff(numbers, length) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

void Test1()
{
    int numbers[] = { 4, 1, 3, 2, 5 };
    Test("Test1", numbers, sizeof(numbers) / sizeof(int), 4);
}

// 价格递增
void Test2()
{
    int numbers[] = { 1, 2, 4, 7, 11, 16 };
    Test("Test2", numbers, sizeof(numbers) / sizeof(int), 15);
}

// 价格递减
void Test3()
{
    int numbers[] = { 16, 11, 7, 4, 2, 1 };
    Test("Test3", numbers, sizeof(numbers) / sizeof(int), -1);
}

// 价格全部相同
void Test4()
{
    int numbers[] = { 16, 16, 16, 16, 16 };
    Test("Test4", numbers, sizeof(numbers) / sizeof(int), 0);
}

void Test5()
{
    int numbers[] = { 9, 11, 5, 7, 16, 1, 4, 2 };
    Test("Test5", numbers, sizeof(numbers) / sizeof(int), 11);
}

void Test6()
{
    int numbers[] = { 2, 4 };
    Test("Test6", numbers, sizeof(numbers) / sizeof(int), 2);
}

void Test7()
{
    int numbers[] = { 4, 2 };
    Test("Test7", numbers, sizeof(numbers) / sizeof(int), -2);
}

void Test8()
{
    Test("Test8", nullptr, 0, 0);
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
    Test8();
}

int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 3, 2, 6, 4 };

    //bool res = solver.IsContinuous(data);
    //cout << res << endl;

    return 0;
}
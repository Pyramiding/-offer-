//
// Created by W on 2019/3/7 0007.
//
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

int GetNumberSameAsIndex(const int* numbers, int length)
{
    if(numbers == nullptr || length <= 0)
        return -1;

    int left = 0;
    int right = length - 1;
    while(left <= right)
    {
        int middle = (right + left) >> 1;
        if(numbers[middle] < middle)
            left = middle + 1;
        else if(numbers[middle] > middle)
            right = middle - 1;
        else
            return middle;
    }

    return -1;
}


// ====================测试代码====================
void Test(const char* testName, int numbers[], int length, int expected)
{
    if(GetNumberSameAsIndex(numbers, length) == expected)
        printf("%s passed.\n", testName);
    else
        printf("%s FAILED.\n", testName);
}

void Test1()
{
    int numbers[] = { -3, -1, 1, 3, 5 };
    int expected = 3;
    Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test2()
{
    int numbers[] = { 0, 1, 3, 5, 6 };
    int expected = 0;
    Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test3()
{
    int numbers[] = { -1, 0, 1, 2, 4 };
    int expected = 4;
    Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test4()
{
    int numbers[] = { -1, 0, 1, 2, 5 };
    int expected = -1;
    Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test5()
{
    int numbers[] = { 0 };
    int expected = 0;
    Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test6()
{
    int numbers[] = { 10 };
    int expected = -1;
    Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test7()
{
    Test("Test7", nullptr, 0, -1);
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
    Solution solver;
    vector<int> data = {1, 2, 3, 3, 3, 3, 4, 5};
    //printf("%d", solver.GetNumberOfK(data, 3));
    return 0;
}
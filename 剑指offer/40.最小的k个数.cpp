//
// Created by W on 2019/3/1 0001.
//

// 面试题40：最小的k个数
// 题目：输入n个整数，找出其中最小的k个数。例如输入4、5、1、6、2、7、3、8
// 这8个数字，则最小的4个数字是1、2、3、4。

#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
#include <functional>

#include "Utilities\Array.h"

using namespace std;

//
// NowCoder提交格式
//

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(const vector<int> input, int k)
    {
        multiset<int, greater<int> > leastNumbers;
        leastNumbers.clear();
        vector<int> result;

        if(k < 1 || input.size() < k)
            return result;

        for(auto elmt: input)
        {
            if(leastNumbers.size() < k)
                leastNumbers.insert(elmt);
            else
            {
                if(elmt < *(leastNumbers.begin()))
                {
                    leastNumbers.erase(leastNumbers.begin());
                    leastNumbers.insert(elmt);
                }
            }
        }

        for(auto elmt: leastNumbers)
            result.push_back(elmt);
        return result;
    }

private:
};

// ====================方法1====================
void GetLeastNumbers_Solution1(int* input, int n, int* output, int k)
{
    if(!input || !output || n <= 0 || k > n || k <= 0)
        return;

    int start = 0, end = n - 1;
    int index = Partition(input, n, start, end);
    while(index != k - 1)
    {
        if(index > k - 1)
        {
            end = index - 1;
            index = Partition(input, n, start, end);
        }
        else
        {
            start = index + 1;
            index = Partition(input, n, start, end);
        }

        for(int i = 0; i < k; i++)
            output[i] = input[i];
    }


}

// ====================方法2====================
typedef multiset<int, greater<int> > intSet;

void GetLeastNumbers_Solution2(const vector<int>& data, intSet& leastNumbers, int k)
{
    leastNumbers.clear();

    if(k < 1 || data.size() < k)
        return;

    for(auto elmt: data)
    {
        if(leastNumbers.size() < k)
            leastNumbers.insert(elmt);
        else
        {
            if(elmt < *(leastNumbers.begin()))
            {
                leastNumbers.erase(leastNumbers.begin());
                leastNumbers.insert(elmt);
            }
        }
    }
}


// ====================测试代码====================
void Test(const char* testName, int* data, int n, int* expectedResult, int k)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    vector<int> vectorData;
    for(int i = 0; i < n; ++ i)
        vectorData.push_back(data[i]);

    if(expectedResult == nullptr)
        printf("The input is invalid, we don't expect any result.\n");
    else
    {
        printf("Expected result: \n");
        for(int i = 0; i < k; ++ i)
            printf("%d\t", expectedResult[i]);
        printf("\n");
    }

    printf("Result for solution1:\n");
    int* output = new int[k];
    GetLeastNumbers_Solution1(data, n, output, k);
    if(expectedResult != nullptr)
    {
        for(int i = 0; i < k; ++ i)
            printf("%d\t", output[i]);
        printf("\n");
    }

    delete[] output;

    printf("Result for solution2:\n");
    intSet leastNumbers;
    GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
    printf("The actual output numbers are:\n");
    for(auto iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
        printf("%d\t", *iter);
    printf("\n\n");
}

// k小于数组的长度
void Test1()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4};
    Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
void Test2()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
void Test3()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
void Test4()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1};
    Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
void Test5()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
void Test6()
{
    int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
    int expected[] = {1, 2};
    Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
void Test7()
{
    int* expected = nullptr;
    Test("Test7", nullptr, 0, expected, 0);
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



int main(int argc, char* argv[]) {
    manytest();
    return 0;
}
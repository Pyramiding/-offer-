//
// Created by W on 2019/3/5 0005.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    int GetUglyNumber_Solution1(int index) {
        if(index <= 0)
            return 0;

        vector<int> uglyNumbers(index, 1);
        //vector<int> uglyNumbers = {1};
        int nextUglyIndex = 1;

        auto pMultiply2 = uglyNumbers.begin();
        auto pMultiply3 = uglyNumbers.begin();
        auto pMultiply5 = uglyNumbers.begin();

        while(nextUglyIndex < index)
        {
            int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
            uglyNumbers[nextUglyIndex] = min;
            //uglyNumbers.push_back(min); 注意push操作会使迭代器失效，指向不明

            while(*pMultiply2 * 2 <= uglyNumbers[nextUglyIndex])
                ++pMultiply2;
            while(*pMultiply3 * 3 <= uglyNumbers[nextUglyIndex])
                ++pMultiply3;
            while(*pMultiply5 * 5 <= uglyNumbers[nextUglyIndex])
                ++pMultiply5;

            ++nextUglyIndex;
        }
        return uglyNumbers[index - 1];
    }

    int Min(int num1, int num2, int num3)
    {
        int min = (num1 < num2) ? num1 : num2;
        min = (min < num3) ? min : num3;
        return min;
    }

    int GetUglyNumber_Solution(int index)
    {
        if(index < 7)
            return index;
        vector<int> res(index, 1);
        int t2 = 0, t3 = 0, t5 = 0, nextUgly;
        for(nextUgly = 1; nextUgly < index; ++nextUgly)
        {
            res[nextUgly] = min(res[t2] * 2, min(res[t3] * 3, res[t5] * 5));
            if (res[nextUgly] == res[t2] * 2)
                t2++;
            if (res[nextUgly] == res[t3] * 3)
                t3++;
            if (res[nextUgly] == res[t5] * 5)
                t5++;
        }
        return res[index - 1];
    }

private:
};

// ====================算法1的代码====================
bool isUgly(int number)
{
    while(number % 2 == 0)
        number /= 2;
    while(number % 3 == 0)
        number /= 3;
    while(number % 5 == 0)
        number /= 5;

    return number == 1;
}

int getUglyNumber_Solution1(int index)
{
    if(index <= 0)
        return 0;

    int number = 0, uglyFound = 0;
    while(uglyFound < index)
    {
        ++number;
        if(isUgly(number))
            ++uglyFound;
    }
    return number;
}

// ====================算法2的代码====================
int Min(int number1, int number2, int number3);

int getUglyNumber_Solution2(int index)
{
    if(index <= 0)
        return 0;

    int* pUglyNumbers = new int[index];
    pUglyNumbers[0] = 1;
    int nextUglyIndex = 1;

    int* pMultiply2 = pUglyNumbers;
    int* pMultiply3 = pUglyNumbers;
    int* pMultiply5 = pUglyNumbers;

    while(nextUglyIndex < index)
    {
        int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
        pUglyNumbers[nextUglyIndex] = min;

        while(*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply2;
        while(*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply3;
        while(*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
            ++pMultiply5;

        ++nextUglyIndex;
    }

    int ugly = pUglyNumbers[nextUglyIndex - 1];
    delete[] pUglyNumbers;
    return ugly;
}


int Min(int number1, int number2, int number3)
{
    int min = (number1 < number2) ? number1 : number2;
    min = (min < number3) ? min : number3;

    return min;
}

// ====================测试代码====================
void Test(int index, int expected)
{
    if(getUglyNumber_Solution1(index) == expected)
        printf("solution1 passed\n");
    else
        printf("solution1 failed\n");

    if(getUglyNumber_Solution2(index) == expected)
        printf("solution2 passed\n");
    else
        printf("solution2 failed\n");
}


void manytest()
{
    Test(1, 1);

    Test(2, 2);
    Test(3, 3);
    Test(4, 4);
    Test(5, 5);
    Test(6, 6);
    Test(7, 8);
    Test(8, 9);
    Test(9, 10);
    Test(10, 12);
    Test(11, 15);

    Test(1500, 859963392);

    Test(0, 0);
}


int main(int argc, char* argv[])
{
    //manytest();

    vector<int> push = {1, -2, 3, 10, -4, 7, 2, -5};
    Solution solver;
    int res = solver.GetUglyNumber_Solution(1500);
    cout << res << "  ";

    //1 2 3 4 5 6 8 9 10 12 15
    return 0;
}
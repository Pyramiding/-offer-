//
// Created by W on 2019/3/4 0004.
//
// 面试题44：数字序列中某一位的数字
// 题目：数字以0123456789101112131415…的格式序列化到一个字符序列中。在这
// 个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。请写一
// 个函数求任意位对应的数字。

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;

//
// NowCoder提交格式
//

class Solution {
public:

private:
};

int countOfIntegers(int digits);
int digitAtIndex(int index, int digits);
int beginNumber(int digits);

int digitAtIndex(int index)
{
    if(index < 0)
        return -1;

    // digits位数字
    int digits = 1;
    while(true)
    {
        int numbers = countOfIntegers(digits);
        if(index < numbers * digits)
            return digitAtIndex(index, digits);

        index -= digits * numbers;
        digits++;
    }

    return -1;
}

// digits位的数字总共多少个
int countOfIntegers(int digits)
{
    if(digits == 1)
        return 10;

    int count = (int) pow(10, digits - 1);
    return 9 * count;
}

// 在digits位数中寻找index位置的数字，
// 此时index不包括前面已经排除的低位数的数字
int digitAtIndex(int index, int digits)
{
    int number = beginNumber(digits) + index / digits; //index位数字在数字number中
    int indexFromRight = digits - index % digits; //数字number从右数indexFromRight位
    for(int i = 1; i < indexFromRight; ++i)
        number /= 10;
    return number % 10; //取出数字number中从右数indexFromRight位
}

// digits 位数字的第一个数字
int beginNumber(int digits)
{
    if(digits == 1)
        return 0;

    return (int) pow(10, digits - 1);
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
    if(digitAtIndex(inputIndex) == expectedOutput)
        cout << testName << " passed." << endl;
    else
        cout << testName << " FAILED." << endl;
}


void manytest()
{
    test("Test1", 0, 0);
    test("Test2", 1, 1);
    test("Test3", 9, 9);
    test("Test4", 10, 1);
    test("Test5", 189, 9);  // 数字99的最后一位，9
    test("Test6", 190, 1);  // 数字100的第一位，1
    test("Test7", 1000, 3); // 数字370的第一位，3
    test("Test8", 1001, 7); // 数字370的第二位，7
    test("Test9", 1002, 0); // 数字370的第三位，0
}

int main(int argc, char* argv[])
{
    manytest();
    /*
    vector<int> push = {1, -2, 3, 10, -4, 7, 2, -5};
    Solution solver;
    int res = solver.FindGreatestSumOfSubArray(push);
    cout << res << "  ";*/

    //cout << boolalpha << ret << endl;

    return 0;
}
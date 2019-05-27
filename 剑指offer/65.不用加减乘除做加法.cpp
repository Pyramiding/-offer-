//
// Created by W on 2019/3/11 0011.
//
// 面试题65：不用加减乘除做加法
// 题目：写一个函数，求两个整数之和，要求在函数体内不得使用＋、－、×、÷
// 四则运算符号。

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

int Add(int num1, int num2)
{
    int sum, carry;
    do{
        sum = num1 ^ num2;
        carry = (num1 & num2) << 1;

        num1 = sum;
        num2 = carry;
    }while(num2 != 0);

    return num1;

}

//不使用新变量交换两个变量的值
//基于加减法
int Exchange1(int& num1, int& num2)
{
    num1 = num1 + num2;
    num2 = num1 - num2;
    num1 = num1 - num2;
}
//基于异或运算
int Exchange2(int& num1, int& num2)
{
    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;
}

// ====================测试代码====================
void Test(int num1, int num2, int expected)
{
    int result = Add(num1, num2);
    if(result == expected)
        printf("%d + %d is %d. Passed\n", num1, num2, result);
    else
        printf("%d + %d is %d. FAILED\n", num1, num2, result);
}

void manytest()
{
    Test(1, 2, 3);
    Test(111, 899, 1010);

    Test(-1, 2, 1);
    Test(1, -2, -1);

    Test(3, 0, 3);
    Test(0, -4, -4);

    Test(-2, -8, -10);
}


int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 3, 2, 6, 4 };

    //int res = solver.Sum_Solution(10);
    //cout << res << endl;

    return 0;
}
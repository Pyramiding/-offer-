//
// Created by W on 2019/3/11 0011.
//
// 面试题64：求1+2+…+n
// 题目：求1+2+…+n，要求不能使用乘除法、for、while、if、else、switch、case
// 等关键字及条件判断语句（A?B:C）。

#include <iostream>
#include <cstdio>
using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    int Sum_Solution(int n) {
        int ans = n;
        ans && (ans += Sum_Solution(n - 1)); //利用短路逻辑，ans为0时&&后不执行
        return ans;
    }
private:
};

// ====================方法一====================
class Temp
{
public:
    Temp() { ++N; Sum += N; }
    static void Reset() { N = 0; Sum = 0; }
    static unsigned int GetSum() { return Sum; }

private:
    static unsigned int N;
    static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_Solution1(unsigned int n)
{
    Temp::Reset();
    Temp* a = new Temp[n]; //类数组，维度为n，n次构造函数
    delete []a;
    a = nullptr;

    return Temp::GetSum();
}

// ====================方法二====================
class A;
A* Array[2];

class A
{
public:
    virtual unsigned int Sum(unsigned int n)
    {
        return 0;
    }
};

class B: public A
{
public:
    virtual unsigned int Sum(unsigned int n)
    {
        return Array[n != 0]->Sum(n-1) + n;
    }
};

int Sum_Solution2(int n)
{
    A a;
    B b;
    Array[0] = &a;
    Array[1] = &b;

    int value = Array[1]->Sum(n);

    return value;
}

// ====================方法三====================
typedef unsigned int (*fun)(unsigned int);

unsigned int Solution3_Teminator(unsigned int n)
{
    return 0;
}

unsigned int Sum_Solution3(unsigned int n)
{
    static fun f[2] = {Solution3_Teminator, Sum_Solution3};
    return n + f[n != 0](n - 1);
}

// ====================方法三====================
template <unsigned int n> struct Sum_Solution4
{
    enum Value { N = Sum_Solution4<n - 1>::N + n};
};

template <> struct Sum_Solution4<1>
{
    enum Value { N = 1};
};

template <> struct Sum_Solution4<0>
{
    enum Value { N = 0};
};

// ====================测试代码====================
void Test(int n, int expected)
{
    printf("Test for %d begins:\n", n);

    if(Sum_Solution1(n) == expected)
        printf("Solution1 passed.\n");
    else
        printf("Solution1 failed.\n");

    if(Sum_Solution2(n) == expected)
        printf("Solution2 passed.\n");
    else
        printf("Solution2 failed.\n");

    if(Sum_Solution3(n) == expected)
        printf("Solution3 passed.\n");
    else
        printf("Solution3 failed.\n");
}

void Test1()
{
    const unsigned int number = 1;
    int expected = 1;
    Test(number, expected);
    if(Sum_Solution4<number>::N == expected)
        printf("Solution4 passed.\n");
    else
        printf("Solution4 failed.\n");
}

void Test2()
{
    const unsigned int number = 5;
    int expected = 15;
    Test(number, expected);
    if(Sum_Solution4<number>::N == expected)
        printf("Solution4 passed.\n");
    else
        printf("Solution4 failed.\n");
}

void Test3()
{
    const unsigned int number = 10;
    int expected = 55;
    Test(number, expected);
    if(Sum_Solution4<number>::N == expected)
        printf("Solution4 passed.\n");
    else
        printf("Solution4 failed.\n");
}

void Test4()
{
    const unsigned int number = 0;
    int expected = 0;
    Test(number, expected);
    if(Sum_Solution4<number>::N == expected)
        printf("Solution4 passed.\n");
    else
        printf("Solution4 failed.\n");
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
}

int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 3, 2, 6, 4 };

    int res = solver.Sum_Solution(10);
    cout << res << endl;

    return 0;
}
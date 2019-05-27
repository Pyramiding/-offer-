//
// Created by W on 2019/3/10 0010.
//

// 面试题62：圆圈中最后剩下的数字
// 题目：0, 1, …, n-1这n个数字排成一个圆圈，从数字0开始每次从这个圆圈里
// 删除第m个数字。求出这个圆圈里剩下的最后一个数字。

#include <iostream>
#include <cstdio>
#include <list>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
private:
};

// ====================方法1====================
int LastRemaining_Solution1(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;

    list<int> numbers;// 双向链表，支持双向顺序访问，不支持随机访问
    for(int i = 0; i < n; ++i)
        numbers.push_back(i);

    auto current = numbers.begin();
    while(numbers.size() > 1)
    {
        for(int i = 1; i < m; ++i)
        {
            current++;
            if(current == numbers.end())
                current = numbers.begin();//最后一位连接到第一位
        }

        auto next = ++current;
        if(next == numbers.end())
            next = numbers.begin();

        --current;
        numbers.erase(current); //删除迭代器指定的元素
        current = next;
    }

    return *(current);
}

// ====================方法2====================
int LastRemaining_Solution2(unsigned int n, unsigned int m)
{
    if(n < 1 || m < 1)
        return -1;

    int last = 0;
    for (int i = 2; i <= n; i ++)
        last = (last + m) % i;

    return last;
}

// ====================测试代码====================
void Test(const char* testName, unsigned int n, unsigned int m, int expected)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    if(LastRemaining_Solution1(n, m) == expected)
        printf("Solution1 passed.\n");
    else
        printf("Solution1 failed.\n");

    if(LastRemaining_Solution2(n, m) == expected)
        printf("Solution2 passed.\n");
    else
        printf("Solution2 failed.\n");

    printf("\n");
}

void Test1()
{
    Test("Test1", 5, 3, 3);
}

void Test2()
{
    Test("Test2", 5, 2, 2);
}

void Test3()
{
    Test("Test3", 6, 7, 4);
}

void Test4()
{
    Test("Test4", 6, 6, 3);
}

void Test5()
{
    Test("Test5", 0, 0, -1);
}

void Test6()
{
    Test("Test6", 4000, 997, 1027);
}

void manytest()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
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
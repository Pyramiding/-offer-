//
// Created by W on 2019/3/8 0008.
//
// 面试题57（二）：为s的连续正数序列
// 题目：输入一个正数s，打印出所有和为s的连续正数序列（至少含有两个数）。
// 例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、
// 4～6和7～8。

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum)
    {
        vector<vector<int> > res;
        if(sum < 3)
            return res;

        int small = 1, big = 2;
        int middle = (1 + sum) >> 1;
        int curSum = small + big;

        while(small < middle && big < sum)
        {
            while(curSum > sum)
            {
                curSum -= small;
                small++;
            }
            if (curSum == sum)
                InsertRes(small, big, res);
            big++;
            curSum += big;
        }
        return res;
    }

    void InsertRes(int begin, int end, vector<vector<int> >& res)
    {
        vector<int> temp;
        for(int i = begin; i <= end; i++)
            temp.push_back(i);
        res.push_back(temp);
    }

private:
};

void PrintContinuousSequence(int small, int big);

void FindContinuousSequence(int sum)
{
    if(sum < 3)
        return;

    int small = 1, big = 2;
    int middle = (1 + sum) / 2;
    int curSum = small + big;
    while(small < middle)
    {
        if(curSum == sum)
            PrintContinuousSequence(small, big);

        while(curSum > sum && small < middle)
        {
            curSum -= small;
            small++;

            if(curSum == sum)
                PrintContinuousSequence(small, big);
        }

        big++;
        curSum += big;
    }
}

void PrintContinuousSequence(int small, int big)
{
    for(int i = small; i <= big; ++ i)
        printf("%d ", i);

    printf("\n");
}


// ====================测试代码====================
void Test(const char* testName, int sum)
{
    if(testName != nullptr)
        printf("%s for %d begins: \n", testName, sum);

    FindContinuousSequence(sum);
}

void manytest()
{
    Test("test1", 1);
    Test("test2", 3);
    Test("test3", 4);
    Test("test4", 9);
    Test("test5", 15);
    Test("test6", 100);
}

int main(int argc, char* argv[])
{
    //manytest();
    Solution solver;
    vector<int> data = {1, 2, 3, 3, 3, 3, 4, 5};
    auto res = solver.FindContinuousSequence(3);
    for(auto elmt1: res)
    {
        for(auto elmt2 : elmt1)
            printf("%d ", elmt2);
        printf("\n");
    }

    return 0;
}
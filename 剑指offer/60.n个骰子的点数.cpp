//
// Created by W on 2019/3/10 0010.
//
// 面试题60：n个骰子的点数
// 题目：把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s
// 的所有可能的值出现的概率。

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
private:
};

int g_maxValue = 6;
// ====================方法一：递归====================
void Probability(int number, int* pProbabilities);
void Probability(int original, int current, int sum, int* pProbabilities);

void PrintProbability_Solution1(int number)
{
    if(number < 1)
        return;

    int maxSum = number * g_maxValue;
    int* pProbabilities = new int[maxSum - number + 1];
    for(int i = number; i <= maxSum; ++i)
        pProbabilities[i - number] = 0;

    Probability(number, pProbabilities);

    //输出每个点数的概率和
    int total = int(pow(g_maxValue, number));
    for(int i = number; i <= maxSum; ++i)
    {
        double ratio = (double)pProbabilities[i - number] / total;
        printf("%d: %e\n", i, ratio);
    }

    delete[] pProbabilities;
}

void Probability(int number, int* pProbabilities)
{
    for(int i = 1; i <= g_maxValue; ++i)
        Probability(number, number, i, pProbabilities);
}

void Probability(int original, int current, int sum, int* pProbabilities)
{
    if(current == 1)
        pProbabilities[sum - original]++;
    else
        for(int i = 1; i <= g_maxValue; ++i)
            Probability(original, current - 1, i + sum, pProbabilities);
}

// ====================方法二====================
void PrintProbability_Solution2(int number)
{
    if(number < 1)
        return;
    int* pProbabilities[2];
    pProbabilities[0] = new int[g_maxValue * number + 1];
    pProbabilities[1] = new int[g_maxValue * number + 1];
    for(int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }

    int flag = 0;
    for(int i = 1; i < g_maxValue; ++i)
        pProbabilities[flag][i] = 1; // 一个骰子点数为1~6次数为1

    for(int k = 2; k <= number; ++k) //骰子数目逐渐增加，2~number
    {
        for(int i = 0; i < k; ++i)
            pProbabilities[1-flag][i] = 0; //清零，k骰子0~k-1点数次数为0

        for(int i = k; k <= g_maxValue * k; ++i)
        {
            pProbabilities[1 - flag][i] = 0;//清零，清除上次保存的数据
            for(int j = 1; j <= i && j <= g_maxValue; ++j)
                pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];//将另一数组i-1~i-6位上数字相加
        }

        flag = 1 - flag;//翻转数组
    }

    double total = pow((double)g_maxValue, number);
    for(int i = number; i <= g_maxValue * number; ++i)
    {
        double ratio = (double)pProbabilities[flag][i] / total;
        printf("%d: %e\n", i, ratio);
    }

    delete[] pProbabilities[0];
    delete[] pProbabilities[1];
}

// ====================测试代码====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);

    printf("Test for solution1\n");
    PrintProbability_Solution1(n);

    printf("Test for solution2\n");
    PrintProbability_Solution2(n);

    printf("\n");
}

void manytest()
{
    Test(1);
    Test(2);
    Test(3);
    Test(4);

    Test(11);

    Test(0);
}

int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 2, 3, 3, 3, 3, 4, 5};

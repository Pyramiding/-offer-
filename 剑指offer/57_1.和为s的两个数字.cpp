//
// Created by W on 2019/3/8 0008.
//
// 面试题57（一）：和为s的两个数字
// 题目：输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们
// 的和正好是s。如果有多对数字的和等于s，输出任意一对即可。

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
    // 输出两个数的乘积最小的。
    // 可以用二次函数证明和固定的两数，两数距离越远，乘积越小。
    // 故找到的第一组（相差最大的）就是乘积最小的。
    vector<int> FindNumbersWithSum(vector<int>& array, int sum)
    {
        int length = array.size();
        vector<int> res;
        if(length < 1 || array[0] + array[1] > sum || array[length - 2] + array[length - 1] < sum)
            return res;

        int ahead = length - 1;
        int behind = 0;

        while(ahead > behind)
        {
            long long curSum = array[ahead] + array[behind];

            if(curSum == sum)
            {
                res.push_back(array[behind]);
                res.push_back(array[ahead]);
                break;
            }
            else if(curSum > sum)
                ahead --;
            else
                behind ++;
        }
        return res;
    }
private:
};

bool FindNumbersWithSum(const int data[], int length, int sum, int* num1, int* num2)
{
    bool found = false;
    if(length < 1 || data[0] + data[1] > sum || data[length - 2] + data[length - 1] < sum)
        return found;

    int ahead = length - 1;
    int behind = 0;

    while(ahead > behind)
    {
        long long curSum = data[ahead] + data[behind];

        if(curSum == sum)
        {
            *num1 = data[behind];
            *num2 = data[ahead];
            found = true;
            break;
        }
        else if(curSum > sum)
            ahead --;
        else
            behind ++;
    }

    return found;
}

// ====================测试代码====================
void Test(const char* testName, int data[], int length, int sum, bool expectedReturn)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    int num1, num2;
    int result = FindNumbersWithSum(data, length, sum, &num1, &num2);
    if(result == expectedReturn)
    {
        if(result)
        {
            if(num1 + num2 == sum)
                printf("Passed. \n");
            else
                printf("FAILED. \n");
        }
        else
            printf("Passed. \n");
    }
    else
        printf("FAILED. \n");
}

// 存在和为s的两个数字，这两个数字位于数组的中间
void Test1()
{
    int data[] = {1, 2, 4, 7, 11, 15};
    Test("Test1", data, sizeof(data) / sizeof(int), 15, true);
}

// 存在和为s的两个数字，这两个数字位于数组的两段
void Test2()
{
    int data[] = {1, 2, 4, 7, 11, 16};
    Test("Test2", data, sizeof(data) / sizeof(int), 17, true);
}

// 不存在和为s的两个数字
void Test3()
{
    int data[] = {1, 2, 4, 7, 11, 16};
    Test("Test3", data, sizeof(data) / sizeof(int), 10, false);
}

// 鲁棒性测试
void Test4()
{
    Test("Test4", nullptr, 0, 0, false);
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
    return 0;
}
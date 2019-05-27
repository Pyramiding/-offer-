//
// Created by W on 2019/3/11 0011.
//

// 面试题66：构建乘积数组
// 题目：给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其
// 中B中的元素B[i] =A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

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
    vector<int> multiply(const vector<int>& A)
    {
        vector<int> res(A.size(), 1);
        if(A.size() > 1)
        {
            res[0] = 1;
            for(int i = 1; i < A.size(); ++i)
                res[i] = res[i - 1] * A[i - 1];

            int temp = 1;
            for(int i = A.size() - 2; i >= 0; --i)
            {
                temp *= A[i + 1];
                res[i] *= temp;
            }
        }
        return res;
    }
private:
};

void BuildProductionArray(const vector<double>& input, vector<double>& output)
{
    int length1 = input.size();
    int length2 = output.size();

    if(length1 == length2 && length1 > 1)
    {
        // 计算前部分乘积C[i], C[i]=C[i-1]*A[i-1]
        output[0] = 1;
        for(int i = 1; i < length1; ++i)
            output[i] = output[i - 1] * input[i - 1];

        //计算后部分乘积D[i], D[i]=D[i+1]*A[i+1]
        //并计算B[i] = C[i]*D[i]
        double temp = 1;
        for(int i = length1 - 2; i >= 0; --i)
        {
            temp *= input[i + 1];
            output[i] *= temp;
        }
    }
}

// ====================测试代码====================
static bool EqualArrays(const vector<double>& input, const vector<double>& output)
{
    int length1 = input.size();
    int length2 = output.size();

    if(length1 != length2)
        return false;

    for(int i = 0; i < length1; ++i)
    {
        if(abs(input[i] - output[i]) > 0.0000001)
            return false;
    }

    return true;
}

static void test(const char* testName, const vector<double>& input,
                 vector<double>& output, const vector<double>& expected)
{
    printf("%s Begins: ", testName);

    BuildProductionArray(input, output);
    if(EqualArrays(output, expected))
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

static void test1()
{
    // 输入数组中没有0
    double input[] = { 1, 2, 3, 4, 5 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 120, 60, 40, 30, 24 };

    //不能将临时变量绑定到常引用上
    vector<double> Input(input, input + sizeof(input) / sizeof(double));
    vector<double> Output(output, output + sizeof(output) / sizeof(double));
    vector<double> Expected(expected, expected + sizeof(expected) / sizeof(double));

    test("Test1", Input, Output, Expected);
}

static void test2()
{
    // 输入数组中有一个0
    double input[] = { 1, 2, 0, 4, 5 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 0, 0, 40, 0, 0 };

    vector<double> Input(input, input + sizeof(input) / sizeof(double));
    vector<double> Output(output, output + sizeof(output) / sizeof(double));
    vector<double> Expected(expected, expected + sizeof(expected) / sizeof(double));

    test("Test1", Input, Output, Expected);
}

static void test3()
{
    // 输入数组中有两个0
    double input[] = { 1, 2, 0, 4, 0 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 0, 0, 0, 0, 0 };

    vector<double> Input(input, input + sizeof(input) / sizeof(double));
    vector<double> Output(output, output + sizeof(output) / sizeof(double));
    vector<double> Expected(expected, expected + sizeof(expected) / sizeof(double));

    test("Test1", Input, Output, Expected);
}

static void test4()
{
    // 输入数组中有正、负数
    double input[] = { 1, -2, 3, -4, 5 };
    double output[] = { 0, 0, 0, 0, 0 };
    double expected[] = { 120, -60, 40, -30, 24 };

    vector<double> Input(input, input + sizeof(input) / sizeof(double));
    vector<double> Output(output, output + sizeof(output) / sizeof(double));
    vector<double> Expected(expected, expected + sizeof(expected) / sizeof(double));

    test("Test1", Input, Output, Expected);
}

static void test5()
{
    // 输入输入中只有两个数字
    double input[] = { 1, -2 };
    double output[] = { 0, 0 };
    double expected[] = { -2, 1 };

    vector<double> Input(input, input + sizeof(input) / sizeof(double));
    vector<double> Output(output, output + sizeof(output) / sizeof(double));
    vector<double> Expected(expected, expected + sizeof(expected) / sizeof(double));

    test("Test1", Input, Output, Expected);
}

void manytest()
{
    test1();
    test2();
    test3();
    test4();
    test5();
}


int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 3, 2, 6, 4 };
    vector<int> input = { 1, 2, 3, 4, 5 };
    double expected[] = { 120, 60, 40, 30, 24 };
    vector<int> res = solver.multiply(input);
    for(int elmt: res)
        cout << elmt << " ";

    return 0;
}
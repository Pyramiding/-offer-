
//
// Created by W on 2019/3/4 0004.
//

// 面试题45：把数组排成最小的数
// 题目：输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼
// 接出的所有数字中最小的一个。例如输入数组{3, 32, 321}，则打印出这3个数
// 字能排成的最小数字321323。

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

//
// NowCoder提交格式
//

class Solution {
public:
    string PrintMinNumber(vector<int> numbers)
    {
        string answer = "";
        sort(numbers.begin(), numbers.end(), cmp);
        for(int i = 0; i < numbers.size(); i++)
            answer += to_string(numbers[i]);

        return answer;
    }

    // sort中的比较函数compare要声明为静态成员函数或全局函数，
    // 不能作为普通成员函数，否则会报错。因为：非静态成员函数
    // 是依赖于具体对象的，而std::sort这类函数是全局的，因此
    // 无法再sort中调用非静态成员函数。静态成员函数或者全局
    // 函数是不依赖于具体对象的, 可以独立访问，无须创建任何对象
    // 实例就可以访问。同时静态成员函数不可以调用类的非静态成员。

    static bool cmp(int a, int b)
    {
        string A = "";
        string B = "";
        A += to_string(a);
        A += to_string(b);
        B += to_string(b);
        B += to_string(a);

        return A < B;
    }
private:
};

int compare(const void* strNumber1, const void* strNumber2);

// int型整数用十进制表示最多只有10位
const int g_MaxNumberLength = 10;

char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

void PrintMinNumber(const int* numbers, int length)
{
    if(!numbers || length <= 0)
        return;

    // 二级指针数组，长度为length，每个元素存储指针，
    // 该指针指向另一个数组，将numbers中每个数字转化为字符串存入
    char** strNumbers = (char**)(new int[length]);
    for(int i = 0; i < length; ++i)
    {
        strNumbers[i] = new char[g_MaxNumberLength + 1];
        sprintf(strNumbers[i], "%d", numbers[i]);
    }

    // 快排算法
    qsort(strNumbers, (size_t)length, sizeof(char*), compare);

    for(int i = 0; i < length; ++i)
        printf("%s", strNumbers[i]);
    printf("\n");

    for(int i = 0; i < length; ++i)
        delete[] strNumbers[i];
    delete[] strNumbers;
}

// 如果[strNumber1][strNumber2] > [strNumber2][strNumber1], 返回值大于0
// 如果[strNumber1][strNumber2] = [strNumber2][strNumber1], 返回值等于0
// 如果[strNumber1][strNumber2] < [strNumber2][strNumber1], 返回值小于0
int compare(const void* strNumber1, const void* strNumber2)
{
    // [strNumber1][strNumber2]
    strcpy(g_StrCombine1, *(const char**)strNumber1);//强制类型转换为双指针，再解一个指针
    strcat(g_StrCombine1, *(const char**)strNumber2);

    // [strNumber2][strNumber1]
    strcpy(g_StrCombine2, *(const char**)strNumber2);
    strcat(g_StrCombine2, *(const char**)strNumber1);

    return strcmp(g_StrCombine1, g_StrCombine2);
}


// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, const char* expectedResult)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    if(expectedResult != nullptr)
        printf("Expected result is: \t%s\n", expectedResult);

    printf("Actual result is: \t");
    PrintMinNumber(numbers, length);

    printf("\n");
}

void Test1()
{
    int numbers[] = {3, 5, 1, 4, 2};
    Test("Test1", numbers, sizeof(numbers)/sizeof(int), "12345");
}

void Test2()
{
    int numbers[] = {3, 32, 321};
    Test("Test2", numbers, sizeof(numbers)/sizeof(int), "321323");
}

void Test3()
{
    int numbers[] = {3, 323, 32123};
    Test("Test3", numbers, sizeof(numbers)/sizeof(int), "321233233");
}

void Test4()
{
    int numbers[] = {1, 11, 111};
    Test("Test4", numbers, sizeof(numbers)/sizeof(int), "111111");
}

// 数组中只有一个数字
void Test5()
{
    int numbers[] = {321};
    Test("Test5", numbers, sizeof(numbers)/sizeof(int), "321");
}

void Test6()
{
    Test("Test6", nullptr, 0, "Don't print anything.");
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

int main(int argc, char* argv[]) {
    manytest();
    return 0;
}
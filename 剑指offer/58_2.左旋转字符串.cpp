//
// Created by W on 2019/3/8 0008.
//
// 面试题58（二）：左旋转字符串
// 题目：字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
// 请定义一个函数实现字符串左旋转操作的功能。比如输入字符串"abcdefg"和数
// 字2，该函数将返回左旋转2位得到的结果"cdefgab"。

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    void Reverse(string& s, int start, int end)
    {
        char temp;
        while(start < end)
        {
            temp = s[start];
            s[start] = s[end];
            s[end] = temp;
            start++;
            end--;
        }
    }

    string LeftRotateString1(string str, int n)
    {
        int length = str.size();
        if(length == 0 || n == 0)
            return str;
        Reverse(str, 0, n - 1);
        Reverse(str, n, length - 1);
        Reverse(str, 0, length - 1);
        return str;
    }

    // 牛客网其他简单答案
    string LeftRotateString(string str, int n)
    {
        int len = str.size();
        if(len == 0)
            return str;
        n = n % len;
        str += str;
        return str.substr(n, len);
    }

private:
};

char* LeftRotateString(char* pStr, int n)
{
    if(pStr)
    {
        int nLength = static_cast<int>(strlen(pStr));
        if(nLength > 0 && n > 0 && n < nLength)
        {
            char* pFirstStart = pStr;
            char* pFirstEnd = pStr + n - 1;
            char* pSecondStart = pStr + n;
            char* pSecondEnd = pStr + nLength - 1;

            // 翻转字符串的前面n个字符
            Reverse(pFirstStart, pFirstEnd);
            // 翻转字符串的后面部分
            Reverse(pSecondStart, pSecondEnd);
            // 翻转整个字符串
            Reverse(pFirstStart, pSecondEnd);
        }
    }

    return pStr;
}

// ====================测试代码====================
void Test(const char* testName, char* input, int num, const char* expectedResult)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    char* result = LeftRotateString(input, num);

    if((input == nullptr && expectedResult == nullptr)
       || (input != nullptr && strcmp(result, expectedResult) == 0))
        printf("Passed.\n\n");
    else
        printf("Failed.\n\n");
}

// 功能测试
void Test1()
{
    char input[] = "abcdefg";
    char expected[] = "cdefgab";

    Test("Test1", input, 2, expected);
}

// 边界值测试
void Test2()
{
    char input[] = "abcdefg";
    char expected[] = "bcdefga";

    Test("Test2", input, 1, expected);
}

// 边界值测试
void Test3()
{
    char input[] = "abcdefg";
    char expected[] = "gabcdef";

    Test("Test3", input, 6, expected);
}

// 鲁棒性测试
void Test4()
{
    Test("Test4", nullptr, 6, nullptr);
}

// 鲁棒性测试
void Test5()
{
    char input[] = "abcdefg";
    char expected[] = "abcdefg";

    Test("Test5", input, 0, expected);
}

// 鲁棒性测试
void Test6()
{
    char input[] = "abcdefg";
    char expected[] = "abcdefg";

    Test("Test6", input, 7, expected);
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
    //manytest();
    Solution solver;
    vector<int> data = {1, 2, 3, 3, 3, 3, 4, 5};
    string s = "abcdefg";
    auto res = solver.LeftRotateString(s, 2);
    cout << res << endl;


    return 0;
}
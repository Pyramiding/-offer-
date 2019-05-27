//
// Created by W on 2019/3/5 0005.
//
// 面试题48：最长不含重复字符的子字符串
// 题目：请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子
// 字符串的长度。假设字符串中只包含从'a'到'z'的字符。

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

// 方法一：蛮力法
bool hasDuplication(const std::string& str, int position[]);

int longestSubstringWithoutDuplication_1(const string& str)
{
    int longest = 0;
    int* position = new int[26];
    for(int start = 0; start < str.length(); ++start)
        for(int end = start; end < str.length(); ++end)
        {
            int count = end - start + 1;
            const string& substring = str.substr(start, count);
            if(!hasDuplication(substring, position))
            {
                if(count > longest)
                    longest = count;
            }
            else
                break;
        }

    delete[] position;
    return longest;
}

bool hasDuplication(const string& str, int position[])
{
    for(int i = 0; i < 26; ++i)
        position[i] = 0;

    for(auto elmt: str)
    {
        int indexInPosition = elmt - 'a';
        if(position[indexInPosition] > 0)
            return true;

        position[indexInPosition] = 1;
    }

    return false;
}


// 方法二：动态规划
int longestSubstringWithoutDuplication_2(const std::string& str)
{
    int curLength = 0;
    int maxLength = 0;

    int* position = new int[26];
    for(int i = 0; i < 26; ++i)
        position[i] = -1;

    for(int i = 0; i < str.length(); ++i)
    {
        int prevIndex = position[str[i] - 'a']; // str[i]上次出现的位置
        if(prevIndex < 0 || i - prevIndex > curLength)
            ++curLength;
        else
        {
            if(curLength > maxLength)
                maxLength = curLength; //遇到重复字符，纪录最大无重复子串

            curLength = i - prevIndex;
        }
        position[str[i] - 'a'] = i;
    }

    if(curLength > maxLength)
        maxLength = curLength;

    delete[] position;
    return maxLength;
}


// ====================测试代码====================
/*void testSolution1(const std::string& input, int expected)
{
    int output = longestSubstringWithoutDuplication_1(input);
    if(output == expected)
        std::cout << "Solution 1 passed, with input: " << input << std::endl;
    else
        std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}*/

void testSolution2(const std::string& input, int expected)
{
    int output = longestSubstringWithoutDuplication_2(input);
    if(output == expected)
        std::cout << "Solution 2 passed, with input: " << input << std::endl;
    else
        std::cout << "Solution 2 FAILED, with input: " << input << std::endl;
}

void test(const std::string& input, int expected)
{
    //testSolution1(input, expected);
    testSolution2(input, expected);
}

void test1()
{
    const std::string input = "abcacfrar";
    int expected = 4;
    test(input, expected);
}

void test2()
{
    const std::string input = "acfrarabc";
    int expected = 4;
    test(input, expected);
}

void test3()
{
    const std::string input = "arabcacfr";
    int expected = 4;
    test(input, expected);
}

void test4()
{
    const std::string input = "aaaa";
    int expected = 1;
    test(input, expected);
}

void test5()
{
    const std::string input = "abcdefg";
    int expected = 7;
    test(input, expected);
}

void test6()
{
    const std::string input = "aaabbbccc";
    int expected = 2;
    test(input, expected);
}

void test7()
{
    const std::string input = "abcdcba";
    int expected = 4;
    test(input, expected);
}

void test8()
{
    const std::string input = "abcdaef";
    int expected = 6;
    test(input, expected);
}

void test9()
{
    const std::string input = "a";
    int expected = 1;
    test(input, expected);
}

void test10()
{
    const std::string input = "";
    int expected = 0;
    test(input, expected);
}

void manytest()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
}


int main(int argc, char* argv[])
{
    manytest();
}
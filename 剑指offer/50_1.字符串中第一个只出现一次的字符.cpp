//
// Created by W on 2019/3/6 0006.
//
// 面试题50（一）：字符串中第一个只出现一次的字符
// 题目：在字符串中找出第一个只出现一次的字符。如
// 输入"abaccdeff"，则输出'b'。

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        if(str.empty())
            return -1;

        const int tableSize = 256;
        unsigned int hashTable[tableSize];
        for(unsigned int i = 1; i < tableSize; ++i)
            hashTable[i] = 0;

        auto iter = str.begin();
        while(iter < str.end())
            hashTable[*(iter++)]++;

        int index = 0;
        while(index < str.length())
        {
            if(hashTable[str[index]] == 1)
                return index;
            index++;
        }

        return -1;
    }
private:
};

char FirstNotRepeatingChar_1(const char* pString)
{
    if(!pString)
        return '\0';

    const int tableSize = 256;
    unsigned int hashTable[tableSize];
    for(unsigned int i = 0; i < tableSize; ++i)
        hashTable[i] = 0;

    const char* pHashKey = pString;
    while(*pHashKey != '\0')
        hashTable[*(pHashKey++)]++;

    pHashKey = pString;
    while(*pHashKey != '\0')
    {
        if(hashTable[*pHashKey] == 1)
            return *pHashKey;

        pHashKey++;
    }

    return '\0';
}

// 本题扩展，使用map创建哈希表，空间复杂度变小
char FirstNotRepeatingChar(const char* pString)
{
    if(!pString)
        return '\0';

    map<char, int> hashTable;

    const char* pHashKey = pString;
    while(*pHashKey != '\0')
    {
        // map插入操作返回pair，构成为<迭代器，布尔值>
        // false，已存在；true，插入成功
        if(!hashTable.insert({*pHashKey, 1}).second)
            hashTable[*pHashKey]++;
        pHashKey++;
    }

    pHashKey = pString;
    while(*pHashKey != '\0')
    {
        if(hashTable[*pHashKey] == 1)
            return *pHashKey;

        pHashKey++;
    }

    return '\0';
}

// 从第一个字符串中删除在第二个字符串中出现过的字符
void deleteFromTwo(char* str1, const char* str2)
{

    if(!str1 || !str2)
        return;

    map<char, int> hashTable;

    const char* pHashKey = str2;
    while(*pHashKey != '\0')
    {
        hashTable.insert({*pHashKey, 1});
        pHashKey++;
    }

    //快慢指针，跳过要删除字符
    char* pSlow = str1;
    char* pFast = str1;
    while (*pFast != '\0')
    {
        // 未出现在第二个字符
        if(hashTable.find(*pFast) == hashTable.end())
        {
            *pSlow = *pFast;
            ++pSlow;
        }
        ++pFast;
    }
    *pSlow = '\0';

}

// 删除字符串中重复出现的字符
void deleteRepetition(char* pString)
{
    if(!pString)
        return;

    map<char, int> hashTable;
    char* pSlow = pString;
    char* pFast = pString;
    while(*pFast != '\0')
    {
        // pSlow跳过出现在哈希表中的字符
        if(hashTable.insert({*pFast, 1}).second)
        {
            *pSlow = *pFast;
            ++pSlow;
        }
        ++pFast;
    }
    *pSlow = '\0';
}

// 变位词
bool Anagram(const char* str1, const char* str2)
{
    if((!str1 && str2)|| (str1 && !str2))
        return true;

    const char* pHashKey = str1;
    map<char, int> hashTable;

    while(*pHashKey != '\0')
    {
        if(!hashTable.insert({*pHashKey, 1}).second)
            hashTable[*pHashKey]++;
        pHashKey++;
    }

    pHashKey = str2;
    while(*pHashKey != '\0')
    {
        if(!hashTable.insert({*pHashKey, 1}).second)
            hashTable[*pHashKey]--;
        pHashKey++;
    }

    auto iter = hashTable.begin();
    for(auto pairs: hashTable)
        if(pairs.second != 0)
            return false;

    return true;
}

// ====================测试代码====================
void Test(const char* pString, char expected)
{
    if(FirstNotRepeatingChar(pString) == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

/*
void manytest()
{
    // 常规输入测试，存在只出现一次的字符
    Test("google", 'l');

    // 常规输入测试，不存在只出现一次的字符
    Test("aabccdbd", '\0');

    // 常规输入测试，所有字符都只出现一次
    Test("abcdefg", 'a');

    // 鲁棒性测试，输入nullptr
    Test(nullptr, '\0');
}
*/

int main(int argc, char* argv[])
{
    // 问题1
    char src1[] = "Wee arei students";
    deleteFromTwo(src1, "aeiou");
    printf("%s\n", src1);

    // 问题2
    char src2[] = "google";
    deleteRepetition(src2);
    printf("%s\n", src2);

    //问题3
    char str3[] = "silent";
    char str4[] = "listen";
    printf("%d\n", Anagram(str3, str4));
    printf("%d\n", Anagram("hello", "llego"));

    //manytest();

    vector<int> push = {1, -2, 3, 10, -4, 7, 2, -5};
    Solution solver;
    int res = solver.FirstNotRepeatingChar("google");
    cout << res << "  ";

    //1 2 3 4 5 6 8 9 10 12 15
    return 0;
}
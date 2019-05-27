//
// Created by W on 2019/3/1 0001.
//

// 面试题38：字符串的排列
// 题目：输入一个字符串，打印出该字符串中字符的所有排列。例如输入字符串abc，
// 则打印出由字符a、b、c所能排列出来的所有字符串abc、acb、bac、bca、cab和cba。

#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <string>

using namespace std;

//
// NowCoder提交格式
//

class Solution {
public:
    vector<string> Permutation(string str) {
        if (!str.empty()) {
            int nSize = str.size();
            Permutation(str, nSize, 0);
        }

        for (auto elmt: permutationSet) {
            permutation.push_back(elmt);
        }

        return permutation;
    }

    void Permutation(string str, int nSize, int n)
    {
        if (n == str.size()) {
            permutationSet.insert(str);
        }

        else {
            Permutation(str, nSize, n + 1);
            for (int i = n+1; i < str.size(); ++i) {
                if (str[n] != str[i]) {
                    char tmp = str[n];
                    str[n] = str[i];
                    str[i] = tmp;

                    Permutation(str, nSize, n + 1);

                    tmp = str[n];
                    str[n] = str[i];
                    str[i] = tmp;
                }
            }
        }
    }
public:
    vector<string> permutation;
    set<string> permutationSet;
};

void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
    if(pStr == nullptr)
        return;
    Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin)
{
    if(*pBegin == '\0')
        printf("%s\n", pStr);
    else
    {
        for(char* pCh = pBegin; *pCh != '\0'; ++ pCh)
        {
            char temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;

            Permutation(pStr, pBegin + 1);

            temp = *pCh;
            *pCh = *pBegin;
            *pBegin = temp;
        }
    }
}

// ====================测试代码====================
void Test(char* pStr)
{
    if(pStr == nullptr)
        printf("Test for nullptr begins:\n");
    else
        printf("Test for %s begins:\n", pStr);

    Permutation(pStr);

    printf("\n");
}

int main(int argc, char* argv[])
{
    //manytest();

    Test(nullptr);

    char string1[] = "";
    Test(string1);

    char string2[] = "a";
    Test(string2);

    char string3[] = "ab";
    Test(string3);

    char string4[] = "abc";
    Test(string4);

/*    vector<int> push = {5, 7, 6, 9, 11, 10, 8};
    Solution solver;
    vector<vector<int> > ret = solver.FindPath(pNode10, 22);
    for(auto elmt1: ret)
    {
        for(auto elmt2: elmt1)
            cout << elmt2 << " ";
        cout << endl;
    }*/

    //cout << boolalpha << ret << endl;

    return 0;
}
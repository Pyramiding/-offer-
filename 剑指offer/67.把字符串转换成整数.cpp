//
// Created by W on 2019/3/11 0011.
//
// 面试题67：把字符串转换成整数
// 题目：请你写一个函数StrToInt，实现把字符串转换成整数这个功能。当然，不
// 能使用atoi或者其他类似的库函数。

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    int StrToInt(string str) {
        if(str.empty())
            return 0;

        int num = 0;
        int i = 0;
        bool minus = false;

        // 过滤前面空格
        while(str[i] == ' ')
            i++;

        if(str[i] == '+')
            i++;
        else if(str[i] == '-') {
            i++;
            minus = true;
        }

        for(; i < str.length(); ++i)
        {
            if(str[i] >= '0' && str[i] <= '9'){
                int flag = minus? -1: 1;
                num = num * 10 + flag * (str[i] - '0');

                // 溢出判断
                if((!minus && num > 0x7FFFFFFF)
                   || (minus && num < (signed int)0x80000000)) {
                    num = 0;
                    break;
                }
            }
            else{
                num = 0;
                break;
            }
        }

        return num;
    }

private:
};

long long StrToIntCore(const char* str, bool minus);

enum Status {kValid = 0, kInvalid};
int g_nStatus = kValid;

int StrToInt(const char* str)
{
    g_nStatus = kInvalid;
    long long num = 0;

    if(str != nullptr && *str != '\0')
    {
        bool minus = false;
        if(*str == '+')
            str ++;
        else if(*str == '-')
        {
            str ++;
            minus = true;
        }

        if(*str != '\0')
            num = StrToIntCore(str, minus);
    }

    return (int)num;
}

long long StrToIntCore(const char* digit, bool minus)
{
    long long num = 0;

    while(*digit != '\0')
    {
        if(*digit >= '0' && *digit <= '9')
        {
            int flag = minus ? -1 : 1;
            num = num * 10 + flag * (*digit - '0');

            if((!minus && num > 0x7FFFFFFF)
               || (minus && num < (signed int)0x80000000))
            {
                num = 0;
                break;
            }

            digit++;
        }
        else
        {
            num = 0;
            break;
        }
    }

    if(*digit == '\0')
        g_nStatus = kValid;

    return num;
}

// ====================测试代码====================
void Test(const char* string)
{
    int result = StrToInt(string);
    if(result == 0 && g_nStatus == kInvalid)
        printf("the input %s is invalid.\n", string);
    else
        printf("number for %s is: %d.\n", string, result);
}

void manytest()
{
    Test(nullptr);

    Test("");

    Test("123");

    Test("+123");

    Test("-123");

    Test("1a33");

    Test("+0");

    Test("-0");

    //有效的最大正整数, 0x7FFFFFFF
    Test("+2147483647");

    Test("-2147483647");

    Test("+2147483648");

    //有效的最小负整数, 0x80000000
    Test("-2147483648");

    Test("+2147483649");

    Test("-2147483649");

    Test("+");

    Test("-");
}


int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 3, 2, 6, 4};
    vector<int> input = {1, 2, 3, 4, 5};
    double expected[] = {120, 60, 40, 30, 24};
    //vector<int> res = solver.multiply(input);
    //for (int elmt: res) cout << elmt << " ";

    return 0;
}
//
// Created by W on 2019/3/3 0003.
//

//本题扩展：字符的所有组合
//参考 https://blog.csdn.net/qianqin_2014/article/details/51598778

#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

//
// NowCoder提交格式
//

class Solutio{
//本题扩展：字符串的所有组合
//二维容器，第二维度保存字符组合
public:
    vector<string> Combination(string str) {
        if (!str.empty()) {
            for(int i = 1; i <= str.size(); ++i)
                Combination(str, i, 0);
        }
        return combination;
    }

    void Combination(string str, int n, int begin) {
        if(n == 0)
            combination.push_back(temp);

        if(begin = str.size())
            return;

        temp.push_back(string[begin]);
        Combination(str, --n, ++begin);
        result.pop_back();
        Combination(str, n, ++begin);
    }

private:
    vector<vector<char>> combination;
    vector<char> temp;
};

static int num = 1;

void Combination(char *string, int number, vector<char> &result);

void Combination(char *string)
{
    if (string == NULL)
    {
        cout << "字符为空" << endl;
        return;
    }
    vector<char> result;
    int i, length = strlen(string);
    for (i = 1; i <= length; ++i)
        Combination(string, i, result);//在长度为string字符串中取出i个组合数
}

void Combination(char *string, int number, vector<char> &result)
{
    if (number == 0)
    {
        printf("第%d个组合\t", num++);

        vector<char>::iterator iter = result.begin();
        for (; iter != result.end(); ++iter)
            printf("%c", *iter);
        printf("\n");
        return;
    }

    if (*string == '\0')
        return;
    result.push_back(*string);
    Combination(string + 1, number - 1, result);
    result.pop_back();
    Combination(string + 1, number, result);
}

void test11()
{
    cout << "\t=======检测空指针=======" << endl;
    Combination(NULL);
    cout << endl;
}

void test12()
{
    cout << "\t=======检测只有分隔符的指针=======" << endl;
    num = 1;
    char str[] = "";
    Combination(str);
    cout << endl;
}

void test13()
{
    cout << "\t=======检测只有一个字符的组合=======" << endl;
    num = 1;
    char str[] = "a";
    Combination(str);
    cout << endl;
}

void test14()
{
    cout << "\t=======检测只有若干个字符的组合=======" << endl;
    num = 1;
    char str[] = "abc";
    Combination(str);
    cout << endl;
}

int main(void)
{
    test11();
    test12();
    test13();
    test14();

    return 0;
}

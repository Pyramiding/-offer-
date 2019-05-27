//
// Created by W on 2019/2/18 0018.
//
//
// ------测试主文件-------
//
// 面试题5：替换空格
// 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入“We are happy.”，
// 则输出“We%20are%20happy.”。

#include <cstdio>
#include <cstring>

/*length 为字符数组str的总容量，大于或等于字符串str的实际长度*/
void ReplaceBlank(char str[], int length)
{
    if(str == nullptr && length <= 0)
        return;

    /*originalLength 为字符串str的实际长度*/
    /*numberOfBlank 为字符串中空格的数目 */
    int originalLength = 0;
    int numberOfBlank = 0;
    int i = 0;
    while(str[i] != '\0')
    {
        ++ originalLength;

        if(str[i] == ' ')
            ++ numberOfBlank;

        ++ i;
    }

    /*newLength 为把空格替换成'%20'之后的长度*/
    int newLength = originalLength + numberOfBlank * 2;
    if(newLength > length)
        return;

    int indexOfOriginal = originalLength;
    int indexOfNew = newLength;
    while(indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
    {
        if(str[indexOfOriginal] == ' ')
        {
            str[indexOfNew--] = '0';
            str[indexOfNew--] = '2';
            str[indexOfNew--] = '%';
        }
        else
        {
            str[indexOfNew--] = str[indexOfOriginal];
        }

        -- indexOfOriginal;
    }
}

// ====================测试代码====================
void Test(const char* testName, char str[], int length, const char* expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    ReplaceBlank(str, length);

    if(expected == nullptr && str == nullptr)
        printf("passed.\n");
    else if(expected == nullptr && str != nullptr)
        printf("failed.\n");
    else if(strcmp(str, expected) == 0)
        printf("passed.\n");
    else
        printf("failed.\n");
}

// 空格在句子中间
void Test1()
{
    const int length = 100;

    char str[length] = "hello world";
    Test("Test1", str, length, "hello%20world");
}

// 空格在句子开头
void Test2()
{
    const int length = 100;

    char str[length] = " helloworld";
    Test("Test2", str, length, "%20helloworld");
}

// 空格在句子末尾
void Test3()
{
    const int length = 100;

    char str[length] = "helloworld ";
    Test("Test3", str, length, "helloworld%20");
}

// 连续有两个空格
void Test4()
{
    const int length = 100;

    char str[length] = "hello  world";
    Test("Test4", str, length, "hello%20%20world");
}

// 传入nullptr
void Test5()
{
    Test("Test5", nullptr, 0, nullptr);
}

// 传入内容为空的字符串
void Test6()
{
    const int length = 100;

    char str[length] = "";
    Test("Test6", str, length, "");
}

//传入内容为一个空格的字符串
void Test7()
{
    const int length = 100;

    char str[length] = " ";
    Test("Test7", str, length, "%20");
}

// 传入的字符串没有空格
void Test8()
{
    const int length = 100;

    char str[length] = "helloworld";
    Test("Test8", str, length, "helloworld");
}

// 传入的字符串全是空格
void Test9()
{
    const int length = 100;

    char str[length] = "   ";
    Test("Test9", str, length, "%20%20%20");
}

//
// NowCoder提交格式
//
class Solution {
public:
    //原题目：替换字符串中的空格
    void replaceSpace(char *str, int length) {
        if (str == nullptr && length <= 0)
            return;
        int originalLength = 0;
        int numberOfBlank = 0;
        int i = 0;
        while (str[i] != '\0')
        {
            ++originalLength;
            if (str[i] == ' ')
                ++numberOfBlank;
            ++i;
        }

        int newLength = originalLength + numberOfBlank * 2;
        if (newLength > length)
            return;

        int indexOfOriginal = originalLength;
        int indexOfNew = newLength;
        while (indexOfOriginal >= 0 && indexOfOriginal < indexOfNew)
        {
            if (str[indexOfOriginal] == ' ')
            {
                str[indexOfNew--] = '0';
                str[indexOfNew--] = '2';
                str[indexOfNew--] = '%';
            }
            else
                str[indexOfNew--] = str[indexOfOriginal];

            indexOfOriginal--;
        }

    }

    //相关题目：合并两个排序好的数组
    void combinationTwoArray(int *arr1, int *arr2, int len1, int len2)
    {
        int newIndex = (len1--) + (len2--) - 1;
        while (len1 >= 0 && len2 >= 0)
        {
            if (arr1[len1] > arr2[len2])
                arr1[newIndex--] = arr1[len1--];
            else
                arr1[newIndex--] = arr2[len2--];
        }

        while (len1 >= 0)
            arr1[newIndex--] = arr1[len1--];
        while (len2 >= 0)
            arr1[newIndex--] = arr2[len2--];

    }
};


int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();

    Solution solver;
    const int length = 100;
    char str[length] = "hello world";
    solver.replaceSpace(str, length);
    printf(str);
    cout << endl;

    int arr1[10] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    int len1 = 3, len2 = 3;
    solver.combinationTwoArray(arr1, arr2, len1 ,len2);
    for (auto elmt : arr1)
        cout << elmt << ' ';
    cout << endl;

    return 0;
}




//
// Created by W on 2019/2/18 0018.
//
// 面试题1：赋值运算符函数
// 题目：如下为类型CMyString的声明，请为该类型添加赋值运算符函数。
//

#include<cstring>
#include<cstdio>

class CMyString
{
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString();

    CMyString& operator = (const CMyString& str);

    void Print();

private:
    char* m_pData;
};

CMyString::CMyString(char *pData){ //默认构造
    if(pData == nullptr){
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else{
        int length = strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString &str){ //拷贝构造
    int length = strlen(str.m_pData);
    m_pData = new char[length + 1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString(){ //析构
    delete[] m_pData;
}

/*
CMyString& CMyString::operator = (const CMyString& str){
    if(this == &str)
        return *this;

    delete []m_pData;
    m_pData = nullptr;

    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);

    return *this;
}
*/

//考虑异常安全性
CMyString& CMyString::operator = (const CMyString& str){
    if (this != &str){
        CMyString strTemp(str);
        char* pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData; //析构临时变量strTemp同时也会释放m_pData原来指向的空间
        m_pData = pTemp;
    }
    return *this;
}

void CMyString::Print(){
    printf("%s", m_pData);
}

// ====================测试代码====================
void Test1()
{
    printf("Test1 begins:\n");

    char text[] = "Hello world";

    CMyString str1(text);
    CMyString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");
}

// 赋值给自己
void Test2()
{
    printf("Test2 begins:\n");

    char text[] = "Hello world";

    CMyString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.Print();
    printf(".\n");
}

// 连续赋值
void Test3()
{
    printf("Test3 begins:\n");

    char text[] = "Hello world";

    CMyString str1(text);
    CMyString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str3.Print();
    printf(".\n");
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    return 0;
}

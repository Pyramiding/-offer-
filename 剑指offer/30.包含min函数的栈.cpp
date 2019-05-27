//
// Created by W on 2019/2/26 0026.
//
// 面试题30：包含min函数的栈
// 题目：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min
// 函数。在该栈中，调用min、push及pop的时间复杂度都是O(1)。

#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    void push(int value)
    {
        m_data.push(value);
        if(m_min.empty() || value < m_min.top())
            m_min.push(value);
        else
            m_min.push(m_min.top());
    }

    void pop()
    {
        assert(!m_data.empty() && !m_min.empty());
        m_min.pop();
        m_data.pop();
    }

    int top()
    {
        return m_min.top();
    }

    int min()
    {
        assert(!m_data.empty() && !m_min.empty());
        return m_min.top();
    }

private:
    stack<int> m_data;
    stack<int> m_min;
};


template <typename T> class StackWithMin
{
public:
    StackWithMin() = default;
    virtual ~StackWithMin() = default;

    T& top();
    const T& top() const;

    void push(const T& value);
    void pop();

    const T& min() const;

    bool empty() const;
    size_t size() const;

private:
    stack<T>   m_data;     // 数据栈，存放栈的所有元素
    stack<T>   m_min;      // 辅助栈，存放栈的最小元素
};

template <typename T> void StackWithMin<T>::push(const T& value)
{
    // 把新元素添加到辅助栈
    m_data.push(value);

    // 当新元素比之前的最小元素小时，把新元素插入辅助栈里；
    // 否则把之前的最小元素重复插入辅助栈里
    if(m_min.size() == 0 || value < m_min.top())
        m_min.push(value);
    else
        m_min.push(m_min.top());
}

template <typename T> void StackWithMin<T>::pop()
{
    assert(m_data.size() > 0 && m_min.size() > 0);

    m_data.pop();
    m_min.pop();
}


template <typename T> const T& StackWithMin<T>::min() const
{
    assert(m_data.size() > 0 && m_min.size() > 0);

    return m_min.top();
}

template <typename T> T& StackWithMin<T>::top()
{
    return m_data.top();
}

template <typename T> const T& StackWithMin<T>::top() const
{
    return m_data.top();
}

template <typename T> bool StackWithMin<T>::empty() const
{
    return m_data.empty();
}

template <typename T> size_t StackWithMin<T>::size() const
{
    return m_data.size();
}

void Test(const char* testName, const StackWithMin<int>& stack, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(stack.min() == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

void manytest()
{
    StackWithMin<int> stack;

    stack.push(3);
    Test("Test1", stack, 3);

    stack.push(4);
    Test("Test2", stack, 3);

    stack.push(2);
    Test("Test3", stack, 2);

    stack.push(3);
    Test("Test4", stack, 2);

    stack.pop();
    Test("Test5", stack, 2);

    stack.pop();
    Test("Test6", stack, 3);

    stack.pop();
    Test("Test7", stack, 3);

    stack.push(0);
    Test("Test8", stack, 0);
}

int main(int argc, char* argv[])
{

    manytest();

    Solution solver;

    solver.push(3);
    cout << boolalpha << (solver.min() == 3) << endl;
    solver.push(4);
    cout << boolalpha << (solver.min() == 3) << endl;
    solver.push(2);
    cout << boolalpha << (solver.min() == 2) << endl;
    solver.push(3);
    cout << boolalpha << (solver.min() == 2) << endl;
    solver.pop();
    cout << boolalpha << (solver.min() == 2) << endl;
    solver.pop();
    cout << boolalpha << (solver.min() == 3) << endl;
    solver.pop();
    cout << boolalpha << (solver.min() == 3) << endl;
    solver.push(0);
    cout << boolalpha << (solver.min() == 0) << endl;

    return 0;
}

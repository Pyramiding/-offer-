//
// Created by W on 2019/3/9 0009.
//
// 面试题59（二）：队列的最大值
// 请定义一个队列并实现函数max得到队列里的最大值，要求函数
// max、push_back和pop_front的时间复杂度都是O(1)。

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
private:
};

template <typename T> class QueueWithMax
{
public:
    QueueWithMax():currentIndex(0){}

    void push_back(T number)
    {
        while(!maximums.empty() && number >= maximums.back().number)
            maximums.pop_back();

        InternalData internalData = {number, currentIndex};
        data.push_back(internalData);
        maximums.push_back(internalData);

        ++currentIndex;
    }

    void pop_front()
    {
        if(maximums.empty())
            throw string("queue is empty");

        if(maximums.front().index == data.front().index)
            maximums.pop_front();

        data.pop_front();
    }

    T max() const
    {
        if(maximums.empty())
            throw string("queue is empty");

        return maximums.front().number;
    }

private:
    struct InternalData
    {
        T number;
        int index;
    };

    deque<InternalData> data; //存储队列所有值
    deque<InternalData> maximums; //存储当前队列最大值
    int currentIndex; //所有加入的数字（包括已经弹出的）中的索引
};

// ====================测试代码====================
void Test(const char* testName, const QueueWithMax<int>& queue, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(queue.max() == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

void manytest()
{
    QueueWithMax<int> queue;
    // {2}
    queue.push_back(2);
    Test("Test1", queue, 2);

    // {2, 3}
    queue.push_back(3);
    Test("Test2", queue, 3);

    // {2, 3, 4}
    queue.push_back(4);
    Test("Test3", queue, 4);

    // {2, 3, 4, 2}
    queue.push_back(2);
    Test("Test4", queue, 4);

    // {3, 4, 2}
    queue.pop_front();
    Test("Test5", queue, 4);

    // {4, 2}
    queue.pop_front();
    Test("Test6", queue, 4);

    // {2}
    queue.pop_front();
    Test("Test7", queue, 2);

    // {2, 6}
    queue.push_back(6);
    Test("Test8", queue, 6);

    // {2, 6, 2}
    queue.push_back(2);
    Test("Test9", queue, 6);

    // {2, 6, 2, 5}
    queue.push_back(5);
    Test("Test9", queue, 6);

    // {6, 2, 5}
    queue.pop_front();
    Test("Test10", queue, 6);

    // {2, 5}
    queue.pop_front();
    Test("Test11", queue, 5);

    // {5}
    queue.pop_front();
    Test("Test12", queue, 5);

    // {5, 1}
    queue.push_back(1);
    Test("Test13", queue, 5);
}

int main(int argc, char* argv[])
{
    manytest();
    Solution solver;
    vector<int> data = {1, 2, 3, 3, 3, 3, 4, 5};
    string s = "abcdefg";

    //auto res = solver.LeftRotateString(s, 2);
    //cout << res << endl;


    return 0;
}
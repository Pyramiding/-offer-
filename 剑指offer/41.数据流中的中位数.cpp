//
// Created by W on 2019/3/3 0003.
//

// 面试题41：数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么
// 中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，
// 那么中位数就是所有数值排序之后中间两个数的平均值。

#include <iostream>
#include <cstdio>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    void Insert(int num)
    {
        if(((min.size() + max.size()) & 1) == 0)//奇数
        {
            if(!max.empty() && num < max[0])
            {
                max.push_back(num);
                push_heap(max.begin(), max.end(), less<int>());
                num = max[0];
                pop_heap(max.begin(), max.end(), less<int>());
                max.pop_back();
            }

            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<int>());
        }
        else
        {
            if(!min.empty() && min[0] < num)
            {
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<int>());
                num = min[0];
                pop_heap(min.begin(), min.end(), greater<int>());
                min.pop_back();
            }

            max.push_back(num);
            push_heap(max.begin(), max.end(), less<int>());
        }
    }

    double GetMedian()
    {
        int size = min.size() + max.size();
        if(size == 0)
            throw string("No numbers are available");

        double median = 0;
        if((size & 1) == 1)
            median = min[0];
        else
            median = (min[0] + max[0]) / 2.0;

        return median;
    }

private:
    vector<int> min;
    vector<int> max;
};

template<typename T> class DynamicArray
{
public:
    void Insert(T num)
    {
        if(((min.size() + max.size()) & 1) == 0)//奇数
        {
            if(!max.empty() && num < max[0])
            {
                max.push_back(num);
                push_heap(max.begin(), max.end(), less<T>());//堆数据插入，最大堆

                num = max[0];

                pop_heap(max.begin(), max.end(), less<T>());//弹出堆顶元素（未删除），将堆顶元素和数组最后一个元素互换
                max.pop_back();
            }

            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<T>());
        }
        else
        {
            if(!min.empty() && min[0] < num)
            {
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());

                num = min[0];

                pop_heap(min.begin(), min.end(), greater<T>());
                min.pop_back();
            }

            max.push_back(num);
            push_heap(max.begin(), max.end(), less<T>());
        }
    }

    T GetMedian()
    {
        int size = min.size() + max.size();
        if(size == 0)
            throw string("No numbers are available");

        T median = 0;
        if((size & 1) == 1)
            median = min[0];
        else
            median = (min[0] + max[0]) / 2;

        return median;
    }

private:
    vector<T> min;//最小堆
    vector<T> max;//最大堆
};

// ====================测试代码====================
void Test(const char* testName, DynamicArray<double>& numbers, double expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(abs(numbers.GetMedian() - expected) < 0.0000001)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
    cout << numbers.GetMedian() << endl;
}


/*void manytest()
{
    DynamicArray<double> numbers;

    printf("Test1 begins: ");
    try
    {
        numbers.GetMedian();
        printf("FAILED.\n");
    }
    catch(const exception&)
    {
        printf("Passed.\n");
    }

    numbers.Insert(5);
    Test("Test2", numbers, 5);

    numbers.Insert(2);
    Test("Test3", numbers, 3.5);

    numbers.Insert(3);
    Test("Test4", numbers, 3);

    numbers.Insert(4);
    Test("Test6", numbers, 3.5);

    numbers.Insert(1);
    Test("Test5", numbers, 3);

    numbers.Insert(6);
    Test("Test7", numbers, 3.5);

    numbers.Insert(7);
    Test("Test8", numbers, 4);

    numbers.Insert(0);
    Test("Test9", numbers, 3.5);

    numbers.Insert(8);
    Test("Test10", numbers, 4);
}*/

int main(int argc, char* argv[])
{
    vector<int> push = {5, 2, 3, 4, 1, 6, 7, 0, 8};
    Solution solver;
    for(auto elmt: push)
    {
        solver.Insert(elmt);
        cout << solver.GetMedian() << "  ";
    }

    //cout << boolalpha << ret << endl;

    return 0;
}
//
// Created by W on 2019/2/26 0026.
//
// 面试题29：顺时针打印矩阵
// 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

//
// NowCoder提交格式
//
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix)
    {
        vector<int> result;

        if(matrix.empty() or matrix[0].empty())
            return result;

        int start = 0;
        int rows = matrix.size();
        int columns = matrix[0].size();

        while(rows > start * 2 && columns > start * 2)
        {
            int endX = columns - 1 - start;
            int endY = rows - 1 - start;

            // 从左到右打印一行
            for(int i = start; i <= endX; ++i)
                result.push_back(matrix[start][i]);

            // 从上到下打印一列
            if(start < endY)
                for(int i = start + 1; i <= endY; ++i)
                    result.push_back(matrix[i][endX]);

            // 从右到左打印一行
            if(start < endX && start < endY)
                for(int i = endX - 1; i >= start; --i)
                    result.push_back(matrix[endY][i]);

            // 从下到上打印一行
            if(start < endX && start < endY - 1)
                for(int i = endY - 1; i >= start + 1; --i)
                    result.push_back(matrix[i][start]);

            ++start;
        }
        return result;
    }

private:
};


void printNumber(int number)
{
    printf("%d\t", number);
}

void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
    int endX = columns - 1 - start;
    int endY = rows - 1 - start;

    // 从左到右打印一行
    for(int i = start; i <= endX; ++i)
    {
        int number = numbers[start][i];
        printNumber(number);
    }

    // 从上到下打印一列
    if(start < endY)
    {
        for(int i = start + 1; i <= endY; ++i)
        {
            int number = numbers[i][endX];
            printNumber(number);
        }
    }

    // 从右到左打印一行
    if(start < endX && start < endY)
    {
        for(int i = endX - 1; i >= start; --i)
        {
            int number = numbers[endY][i];
            printNumber(number);
        }
    }

    // 从下到上打印一行
    if(start < endX && start < endY - 1)
    {
        for(int i = endY - 1; i >= start + 1; --i)
        {
            int number = numbers[i][start];
            printNumber(number);
        }
    }
}


void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
    if(numbers == nullptr || columns <= 0 || rows <= 0)
        return;

    int start = 0;

    while(columns > start * 2 && rows > start * 2)
    {
        PrintMatrixInCircle(numbers, columns, rows, start);

        ++start;
    }
}

// ====================测试代码====================
void Test(int columns, int rows)
{
    printf("Test Begin: %d columns, %d rows.\n", columns, rows);

    if(columns < 1 || rows < 1)
        return;

    int** numbers = new int*[rows];
    for(int i = 0; i < rows; ++i)
    {
        numbers[i] = new int[columns];
        for(int j = 0; j < columns; ++j)
        {
            numbers[i][j] = i * columns + j + 1;
        }
    }

    PrintMatrixClockwisely(numbers, columns, rows);
    printf("\n");

    for(int i = 0; i < rows; ++i)
        delete[] (int*)numbers[i];

    delete[] numbers;
}


void manytest()
{
    /*
1
*/
    Test(1, 1);

    /*
    1    2
    3    4
    */
    Test(2, 2);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    */
    Test(4, 4);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    21   22   23   24   25
    */
    Test(5, 5);

    /*
    1
    2
    3
    4
    5
    */
    Test(1, 5);

    /*
    1    2
    3    4
    5    6
    7    8
    9    10
    */
    Test(2, 5);

    /*
    1    2    3
    4    5    6
    7    8    9
    10   11   12
    13   14   15
    */
    Test(3, 5);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    17   18   19   20
    */
    Test(4, 5);

    /*
    1    2    3    4    5
    */
    Test(5, 1);

    /*
    1    2    3    4    5
    6    7    8    9    10
    */
    Test(5, 2);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14    15
    */
    Test(5, 3);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    */
    Test(5, 4);
}


int main(int argc, char* argv[])
{
    manytest();



    Solution solver;
    vector<vector<int> > arr = {{1, 2, 3, 4, 5},
                                {6, 7, 8, 9, 10},
                                {11, 12, 13, 14, 15},
                                {16, 17, 18, 19, 20}};

    int result = 0;
    vector<int> a = solver.printMatrix(arr);
    for(auto elmt : a)
        cout << elmt << ' ';
    cout << endl;
    cout << result << endl;

    return 0;
}
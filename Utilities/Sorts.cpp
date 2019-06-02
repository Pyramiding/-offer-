//
// Created by W on 2019/3/17 0017.
//

#include <iostream>
#include <vector>
#include <random>
#include "Sorts.h"

using namespace std;

// 生成随机数组
vector<int> Sorts::generateRandomArray(int maxSize, int maxValue)
{
    //vector<int> arr((unsigned int)rand() % (maxSize + 1)); // 产生0~maxSize随机长度的长度数组

    default_random_engine e; // 随机数引擎，负责生成原始随机数
    uniform_int_distribution<> u1(0, maxSize); // 随生成区间[0, maxSize]上的整数
    uniform_int_distribution<> u2(0, maxValue);
    vector<int> arr((unsigned int)u1(e)); // 随生成区间[0, maxValue]上的整数
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = u2(e);
    }
    return arr;
}

// 交换两数
/*
void swap(int& num1, int& num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;

    num1 = num1 + num2;
    num2 = num1 - num2;
    num1 = num1 - num2;

    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;
}
 */

// 冒泡排序
// 时间O(n^2)，最好O(n^2)，最坏O(n^2)
// 空间O(1)，稳定
void Sorts::bubbleSort(vector<int>& arr)
{
    if(arr.size() < 2)
        return;

    // 逐步将大数交换到数组最后
    for (int i = arr.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
// 时间O(n^2)，最好O(n)，最坏O(n^2)
// 空间O(1)，稳定
void Sorts::insertionSort(vector<int>& arr)
{
    if(arr.size() < 2)
        return;

    // 将i位置的数通过交换的方式插入到已经排序的0~i-1位置数组
    // 若arr[j] <= arr[j+1]，直接跳出内层循环
    for (int i = 1; i < arr.size(); i++) {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
            swap(arr[j], arr[j + 1]);
        }
    }
}

// 选择排序
// 时间O(n^2)，最好O(n^2)，最坏O(n^2)
// 空间O(1)，不稳定
void Sorts::selectionSort(vector<int>& arr)
{
    if(arr.size() < 2)
        return;

    // 每次选择i以后的数组中最小数字交换到前面排序好的数组
    for (int i = 0; i < arr.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            minIndex = arr[j] < arr[minIndex] ? j : minIndex;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 希尔排序
// 时间O(n^1.3)
// 空间O(1)，不稳定
void Sorts::shellSort(vector<int>& arr)
{
    int start = 0, end = arr.size() - 1;
    int increment = arr.size() - 1;
    int temp;

    do {    //每次减小增量，直到increment = 1
        increment = increment / 3 + 1;
        for (int i = start + increment; i <= end; ++i) {  //对每个划分进行直接插入排序
            if (arr[i - increment] > arr[i]) {
                temp = arr[i];
                int j = i - increment;
                do {                              //移动元素并寻找位置
                    arr[j + increment] = arr[j];
                    j -= increment;
                } while (j >= start && arr[j] > temp);
                arr[j + increment] = temp;       //插入元素
            }
        }
    } while (increment > 1);

}

// 归并排序
// 时间O(nlogn)，最好O(nlogn)，最坏O(nlogn)
// 空间O(n)，稳定
void Sorts::mergeSort(vector<int>& arr)
{
    if(arr.size() < 2)
        return;

    mergeSort(arr, 0, arr.size() - 1);
}

void Sorts::mergeSort(vector<int>& arr, int l, int r)
{
    if (l == r)
        return;

    int mid = l + ((r - l) >> 1); // 防止溢出
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

void Sorts::merge(vector<int>& arr, int l, int m, int r)
{
    vector<int> help(r - l + 1, 0); // 辅助数组，存储排序好的数组
    int i = 0;
    int p1 = l;
    int p2 = m + 1;
    while (p1 <= m && p2 <= r) {
        help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= m) {
        help[i++] = arr[p1++];
    }
    while (p2 <= r) {
        help[i++] = arr[p2++];
    }
    for (i = 0; i < help.size(); i++) {
        arr[l + i] = help[i];
    }
}

// 堆排序
// 时间O(nlogn)，最好O(nlogn)，最坏O(nlogn)
// 空间O(1)，不稳定
void Sorts::heapSort(vector<int>& arr)
{
    if (arr.size() < 2)
        return;

    for (int i = 0; i < arr.size(); i++) {
        heapInsert(arr, i);
    }

    int size = arr.size();
    swap(arr[0], arr[--size]);
    while (size > 0) {
        heapify(arr, 0, size);
        swap(arr[0], arr[--size]);
    }
}

// 根据数组构建堆，若当前值大于父节点，向上交换
void Sorts::heapInsert(vector<int>& arr, int index)
{
    while (arr[index] > arr[(index - 1) / 2]) {
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// 数组中堆的尺寸为size，当index处值改变时调整成合理的堆
void Sorts::heapify(vector<int>& arr, int index, int size)
{
    int left = index * 2 + 1;
    while (left < size) {
        int largest = left + 1 < size && arr[left + 1] > arr[left] ? left + 1 : left;
        largest = arr[largest] > arr[index] ? largest : index;
        if (largest == index) {
            break;
        }
        swap(arr[largest], arr[index]);
        index = largest;
        left = index * 2 + 1;
    }
}

// 改进的随机快速排序
// 时间O(nlogn)，最好O(nlogn)，最坏O(n^2)
// 空间O(nlogn)，不稳定
void Sorts::quickSort(vector<int>& arr)
{
    if (arr.size() < 2)
        return;

    quickSort(arr, 0, arr.size() - 1);
}

// 递归，对分割后的数组逐步分割排序
void Sorts::quickSort(vector<int>& arr, int l, int r)
{
    if (l < r) {
        int random = rand() % (r - l + 1) + l; // 在l~r中产生一个随机整数
        swap(arr[random], arr[r]);

        vector<int> division = partition(arr, l, r);

        quickSort(arr, l, division[0] - 1);
        quickSort(arr, division[1] + 1, r);
    }
}

// 将数组中的数与随机选择的数random的大小作比较，将数组分为三部分
// 与random相等的放中间，两个分割点放在division中
// less为小于random的左边数组最后一个位置，more为大于random的右边数组第一个位置
vector<int> Sorts::partition(vector<int>& arr, int l, int r)
{
    int less = l - 1;
    int more = r;
    while (l < more) {
        if (arr[l] < arr[r]) {
            swap(arr[++less], arr[l++]);
        } else if (arr[l] > arr[r]) {
            swap(arr[--more], arr[l]);
        } else {
            l++;
        }
    }
    // 将最后一个数调换到中间部分
    swap(arr[more], arr[r]);
    vector<int> division = {less + 1, more};

    return division;
}

//原始快排===========================================
void Sorts::quickSort_old(vector<int>& arr, int l, int r)
{
    if (l < r-1) {
        int q = partition_old(arr, l, r);

        partition_old(arr, l, q);
        quickSort(arr, q+1, r);
    }
}

int Sorts::partition_old(vector<int>& arr, int l, int r)
{
    int x = arr[r-1];
    int i = l-1;
    for(int j = l; j < r-1; j++){
        if(arr[j] <= x){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[r-1]);
    return i+1;
}
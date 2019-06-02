//
// Created by W on 2019/3/17 0017.
//

#ifndef CODINGINTERVIEW_SORTS_H
#define CODINGINTERVIEW_SORTS_H

#include <vector>
using namespace std;

class Sorts
{
public:
    void bubbleSort(vector<int>& arr);
    void insertionSort(vector<int>& arr);
    void selectionSort(vector<int>& arr);
    void shellSort(vector<int>& arr);
    void mergeSort(vector<int>& arr);
    void heapSort(vector<int>& arr);
    void quickSort(vector<int>& arr);

private:
    void mergeSort(vector<int>& arr, int l, int r);
    void merge(vector<int>& arr, int l, int m, int r);
    void heapInsert(vector<int>& arr, int index);
    void heapify(vector<int>& arr, int index, int size);
    void quickSort(vector<int>& arr, int l, int r);
    vector<int> partition(vector<int>& arr, int l, int r);
    vector<int> generateRandomArray(int maxSize, int maxValue);
    void quickSort_old(vector<int>& arr, int l, int r);
    int partition_old(vector<int>& arr, int l, int r);
};

__declspec( dllexport ) void bubbleSort(vector<int>& arr);
__declspec( dllexport ) void insertionSort(vector<int>& arr);
__declspec( dllexport ) void selectionSort(vector<int>& arr);
__declspec( dllexport ) void shellSort(vector<int>& arr);
__declspec( dllexport ) void mergeSort(vector<int>& arr);
__declspec( dllexport ) void heapSort(vector<int>& arr);
__declspec( dllexport ) void quickSort(vector<int>& arr);


#endif //CODINGINTERVIEW_SORTS_H

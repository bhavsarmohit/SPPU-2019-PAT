
// parallel merge sort implemented in C++ using the OpenMP library.
// This code utilizes multiple threads to perform the sorting operation in parallel.

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge two sorted subarrays
void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    // Copy elements to temporary subarrays
    for (int i = 0; i < n1; ++i)
    {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    // Merge the temporary subarrays back into the original array
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            ++i;
        }
        else
        {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of leftArr, if any
    while (i < n1)
    {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    // Copy remaining elements of rightArr, if any
    while (j < n2)
    {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

// Parallel Merge Sort function
void parallelMergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

// The #pragma omp parallel sections directive creates two parallel sections,
// each corresponding to sorting the left and right subarrays.
#pragma omp parallel sections
        {

            // directive to divide the work among multiple threads.
#pragma omp section
            parallelMergeSort(arr, left, mid); // Sort left subarray recursively

// directive to divide the work among multiple threads.
#pragma omp section
            parallelMergeSort(arr, mid + 1, right); // Sort right subarray recursively
        }

        merge(arr, left, mid, right); // Merge the sorted subarrays
    }
}

// Driver program to test parallel Merge Sort
int main()
{
    vector<int> arr = {5, 2, 8, 12, 1, 9};

    cout << "Original Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    parallelMergeSort(arr, 0, arr.size() - 1); // Sort the array using parallel merge sort

    cout << "Sorted Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

// Run
// g++ -fopenmp ParallelMergeSort.cpp -o ParallelMergeSort
// ./ParallelMergeSort

// O/P:
// Original Array: 5 2 8 12 1 9
// Sorted Array: 1 2 5 8 9 12
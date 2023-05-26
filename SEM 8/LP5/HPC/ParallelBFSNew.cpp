#include <iostream>
#include <omp.h>

void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
#pragma omp parallel for
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    bubbleSort(arr, size);

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

// Explaination:
// 1. In the provided code, OpenMP directives are used to parallelize the inner loop of the bubble sort algorithm, allowing multiple iterations of the inner loop to be executed concurrently by multiple threads. The #pragma omp parallel for directive is used to distribute the iterations of the inner loop among the available threads.

// 2. Here's a step-by-step breakdown of the code execution:

// 3. The bubbleSort function takes an array (arr) and its size (size) as input.

// 4. The outer loop (for loop with variable i) iterates from 0 to size - 2 to control the number of passes required to sort the array. Each pass moves the largest element to the end of the array.

// 5. The inner loop (for loop with variable j) iterates from 0 to size - i - 2 and compares adjacent elements of the array. If the current element is greater than the next element, they are swapped.

// 6. The #pragma omp parallel for directive before the inner loop indicates that the iterations of the inner loop can be executed in parallel by multiple threads. OpenMP will automatically distribute the iterations among the available threads.

// 7. Inside the inner loop, the elements are compared and swapped if necessary, which is a common step in the bubble sort algorithm.

// 8. After the sorting is completed, the main function initializes an array (arr) and determines its size.

// 9. The original array is displayed using std::cout.

// 10. The bubbleSort function is called to sort the array.

// 11. The sorted array is displayed using std::cout.

// 12. The program terminates by returning 0 from the main function.

// Note that the output of the program will show the original array and the sorted array.

// Run
// g++ -fopenmp ParallelBFSNew.cpp -o ParallelBFSNew
// ./ParallelBFSNew

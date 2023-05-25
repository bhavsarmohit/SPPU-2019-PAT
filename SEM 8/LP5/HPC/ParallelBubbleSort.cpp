
// parallel bubble sort implemented in C++ using the OpenMP library.
// This code utilizes multiple threads to perform the sorting operation in parallel.

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Parallel Bubble Sort function
// The code starts with the definition of a parallelBubbleSort function,
// which takes a reference to a vector of integers as input.
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();

// The #pragma omp parallel directive creates a parallel region where
// multiple threads will execute the code within the region.
#pragma omp parallel
    {
        // The swapped variable is used to track if any elements were
        // swapped during a pass of the bubble sort algorithm.
        // It is initialized as true.
        bool swapped = true;

        while (swapped)
        {
// The #pragma omp barrier directive ensures that all threads
// synchronize before starting a new pass of the bubble sort
// algorithm. This ensures that each pass is complete before
// proceeding to the next pass.
#pragma omp barrier
            swapped = false;

// The #pragma omp for directive distributes the iterations of the loop among
//  the available threads. Each thread performs the comparison and swapping
//   operations for its assigned range of elements.
#pragma omp for
            for (int i = 0; i < n - 1; ++i)
            {
                if (arr[i] > arr[i + 1])
                {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
        }
    }
}

// Driver program to test parallel Bubble Sort
int main()
{
    vector<int> arr = {5, 2, 8, 12, 1, 9};

    cout << "Original Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    parallelBubbleSort(arr);

    cout << "Sorted Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

// Explanation:

// 1. The code starts with the definition of a parallelBubbleSort function, which takes a reference to a vector of integers as input.

// 2. Inside the parallelBubbleSort function, the total number of elements in the array is obtained using arr.size() and stored in the variable n.

// 3. The #pragma omp parallel directive creates a parallel region where multiple threads will execute the code within the region.

// 4. The swapped variable is used to track if any elements were swapped during a pass of the bubble sort algorithm. It is initialized as true.

// 5. The while loop continues until no elements are swapped, indicating that the array is sorted.

// 6. The #pragma omp barrier directive ensures that all threads synchronize before starting a new pass of the bubble sort algorithm. This ensures that each pass is complete before proceeding to the next pass.

// 7. The #pragma omp for directive distributes the iterations of the loop among the available threads. Each thread performs the comparison and swapping operations for its assigned range of elements.

// 8. Within the loop, adjacent elements are compared, and if the left element is greater than the right element, they are swapped. If any swap occurs, the swapped flag is set to true.

// 9. After the while loop completes, the array is sorted, and the function exits.

// 10. The main function serves as a driver program to test the parallel bubble sort.

// 11. A sample array is initialized, and its elements are printed before sorting.

// 12. The parallelBubbleSort function is called to sort the array in parallel.

// 13. Finally, the sorted array is printed to verify the sorting result.

// Note: The order of elements in the sorted array may vary due to the parallel execution of threads.

// Run
// g++ -o ParallelBubbleSort ParallelBubbleSort.cpp -fopenmp
// ./ParallelBubbleSort

// O/P:
// Original Array: 5 2 8 12 1 9
// Sorted Array: 1 2 5 8 9 12

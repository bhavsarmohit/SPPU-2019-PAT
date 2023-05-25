
// Parallel Reduction Operation Sum, Average, Min, Max
// parallel reduction operations for finding the minimum,
// maximum, sum, and average of an array using OpenMP in C++

#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

// Parallel reduction operation to find the minimum value
int parallelMin(const vector<int> &arr)
{
    int minVal = arr[0];

#pragma omp parallel for reduction(min : minVal)
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] < minVal)
        {
            minVal = arr[i];
        }
    }

    return minVal;
}

// Parallel reduction operation to find the maximum value
int parallelMax(const vector<int> &arr)
{
    int maxVal = arr[0];

#pragma omp parallel for reduction(max : maxVal)
    for (int i = 1; i < arr.size(); ++i)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }

    return maxVal;
}

// Parallel reduction operation to find the sum of the array
int parallelSum(const vector<int> &arr)
{
    int sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < arr.size(); ++i)
    {
        sum += arr[i];
    }

    return sum;
}

// Parallel reduction operation to find the average of the array
double parallelAverage(const vector<int> &arr)
{
    int sum = parallelSum(arr);
    double avg = static_cast<double>(sum) / arr.size();
    return avg;
}

int main()
{
    vector<int> arr = {5, 2, 8, 12, 1, 9};

    cout << "Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    int minVal = parallelMin(arr);
    int maxVal = parallelMax(arr);
    int sum = parallelSum(arr);
    double avg = parallelAverage(arr);

    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;

    return 0;
}

// Explanation:

// The parallelMin function performs the parallel reduction operation to find the minimum value in the array. The reduction(min : minVal) clause ensures that each thread maintains a local copy of minVal and performs the reduction operation using the minimum operator.

// Similarly, the parallelMax function finds the maximum value in the array using the reduction(max : maxVal) clause.

// The parallelSum function calculates the sum of the array elements using the reduction(+: sum) clause.

// The parallelAverage function calls the parallelSum function to calculate the sum and then divides it by the size of the array to find the average.

// In the main function, an example array is initialized.

// The original array is printed.

// The parallelMin, parallelMax, parallelSum, and parallelAverage functions are called to find the minimum, maximum, sum, and average of the array, respectively.

// The results are printed.

// This code utilizes OpenMP directives for parallelization, allowing the reduction operations to be performed efficiently across multiple threads.

// Run
// g++ -fopenmp ParallelReductionOperation.cpp -o ParallelReductionOperation
// ./ParallelReductionOperation

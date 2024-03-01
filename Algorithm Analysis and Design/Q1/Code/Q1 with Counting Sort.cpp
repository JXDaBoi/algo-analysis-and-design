#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <chrono>

using namespace std;

struct parcel
{
    int parcel_ID;
    float cost;
};

parcel *randomParcel(int n)
{
    parcel *array = new parcel[n];

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        array[i].parcel_ID = i + 1;
        array[i].cost = float(rand() % 1000 + 1) + (rand() % 100 / (float)100);
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        int hold_two;
        parcel parcel_hold;

        hold_two = rand() % n;

        parcel_hold = array[i];
        array[i] = array[hold_two];
        array[hold_two] = parcel_hold;
    }

    return array;
}

void countSort(parcel *parcelArray, int size)
{
    // The size of count must be at least the (max+1) but
    // we cannot assign declare it as int count(max+1) in C++ as
    // it does not support dynamic memory allocation.
    // So, its size is provided statically.
    int output[10];
    int count[10];
    int max = parcelArray[0].parcel_ID;

    // Find the largest element of the array
    for (int i = 1; i < size; i++)
    {
        if (parcelArray[i].parcel_ID > max)
            max = parcelArray[i].parcel_ID;
    }

    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i)
    {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < size; i++)
    {
        count[parcelArray[i].parcel_ID]++;
    }

    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = size - 1; i >= 0; i--)
    {
        output[count[parcelArray[i].parcel_ID] - 1] = parcelArray[i].parcel_ID;
        count[parcelArray[i].parcel_ID]--;
    }

    // Copy the sorted elements into original array
    for (int i = 0; i < size; i++)
    {
        parcelArray[i].parcel_ID = output[i];
    }
}

// Function to print an array
void printArray(parcel *parcelArray, int size)
{
    for (int i = 0; i < size; i++)
        cout << parcelArray[i].parcel_ID << endl;
    cout << endl;
}

int main()
{
    bool menu_status = false, show_unsort = false, show_sort = false;

    int sample_size = 1000;
    int trial_runs = 1;

    for (int i = sample_size; i <= sample_size; i++)
    {

        // chrono::seconds *timeArray_second = new chrono::seconds[trial_runs];
        // chrono::milliseconds *timeArray_millisecond = new chrono::milliseconds[trial_runs];
        // chrono::microseconds *timeArray_microsecond = new chrono::microseconds[trial_runs];
        chrono::nanoseconds *timeArray_nanosecond = new chrono::nanoseconds[trial_runs];

        for (int j = 0; j < trial_runs; j++)
        {
            parcel *parcelArray = new parcel[i];

            parcelArray = randomParcel(i);

            auto start = chrono::high_resolution_clock::now();
            countSort(parcelArray, sample_size);
            auto end = chrono::high_resolution_clock::now();

            // timeArray_second[j] = chrono::duration_cast<chrono::seconds>(end - start);
            // timeArray_millisecond[j] = chrono::duration_cast<chrono::milliseconds>(end - start);
            // timeArray_microsecond[j] = chrono::duration_cast<chrono::microseconds>(end - start);
            timeArray_nanosecond[j] = chrono::duration_cast<chrono::nanoseconds>(end - start);
            printArray(parcelArray, sample_size);
        }

        // chrono::seconds total_second = timeArray_second[0], avg_second;
        // chrono::milliseconds total_millisecond = timeArray_millisecond[0], avg_millisecond;
        // chrono::microseconds total_microsecond = timeArray_microsecond[0], avg_microsecond;
        chrono::nanoseconds total_nanosecond = timeArray_nanosecond[0], avg_nanosecond;

        // for (int i = 0; i < trial_runs; i++)
        // {
        //     total_second += timeArray_second[i];
        // }
        // for (int i = 0; i < trial_runs; i++)
        // {
        //     total_millisecond += timeArray_millisecond[i];
        // }
        // for (int i = 0; i < trial_runs; i++)
        // {
        //     total_microsecond += timeArray_microsecond[i];
        // }
        for (int i = 0; i < trial_runs; i++)
        {
            total_nanosecond += timeArray_nanosecond[i];
        }

        // avg_second = total_second / trial_runs;
        // avg_millisecond = total_millisecond / trial_runs;
        // avg_microsecond = total_microsecond / trial_runs;
        avg_nanosecond = total_nanosecond / trial_runs;
        cout << "Time taken to perform the sorting = " << avg_nanosecond.count() << " nanoseconds\n\n";
    }

    return 0;
}
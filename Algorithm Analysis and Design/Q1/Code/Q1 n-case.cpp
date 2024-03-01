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

int partition(parcel *parcelArray, int head, int tail)
{
    int id_hold = parcelArray[tail].parcel_ID;
    int point = head - 1;

    for (int i = head; i < tail; i++)
    {
        if (parcelArray[i].parcel_ID < id_hold)
        {
            point++;
            parcel parcelHold = parcelArray[i];
            parcelArray[i] = parcelArray[point];
            parcelArray[point] = parcelHold;
        }
    }

    parcel parcelHold = parcelArray[tail];
    parcelArray[tail] = parcelArray[point + 1];
    parcelArray[point + 1] = parcelHold;

    return point + 1;
}

void quickSort(parcel *parcelArray, int head, int tail)
{
    if (head < tail)
    {
        int pivot = partition(parcelArray, head, tail);

        quickSort(parcelArray, head, pivot - 1);
        quickSort(parcelArray, pivot + 1, tail);
    }
}

int main()
{
    bool menu_status = false, show_unsort = false, show_sort = false;

    int sample_size = 100000;
    int trial_runs = 1000;

    for (int i = 100000; i <= sample_size; i++)
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
            quickSort(parcelArray, 0, i - 1);
            auto end = chrono::high_resolution_clock::now();

            // timeArray_second[j] = chrono::duration_cast<chrono::seconds>(end - start);
            // timeArray_millisecond[j] = chrono::duration_cast<chrono::milliseconds>(end - start);
            // timeArray_microsecond[j] = chrono::duration_cast<chrono::microseconds>(end - start);
            timeArray_nanosecond[j] = chrono::duration_cast<chrono::nanoseconds>(end - start);

            free(parcelArray);
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

        free(timeArray_nanosecond);

        // avg_second = total_second / trial_runs;
        // avg_millisecond = total_millisecond / trial_runs;
        // avg_microsecond = total_microsecond / trial_runs;
        // avg_nanosecond = total_nanosecond / trial_runs;
        cout << i << endl;
    }

    // cout << "Time taken to perform the sorting = " << avg_second.count() << " seconds\n";
    // cout << "\t\t\t\t  = " << avg_millisecond.count() << " milliseconds\n";
    // cout << "\t\t\t\t  = " << avg_microsecond.count() << " microseconds\n";
    // cout << "\t\t\t\t  = " << avg_nanosecond.count() << " nanoseconds\n\n";

    return 0;
}
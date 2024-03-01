#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <chrono>

using namespace std;

// This is a custom datatype to save both the parcel ID and cost of the parcel
struct parcel
{
    int parcel_ID;
    float cost;
};

// This is a function to generate parcels with random ID and cost
parcel *randomParcel(int n)
{
    parcel *array = new parcel[n];

    srand(time(NULL));

    // Assign the ID by iteration first, and assign random cost
    for (int i = 0; i < n; i++)
    {
        array[i].parcel_ID = i + 1;
        array[i].cost = float(rand() % 1000 + 1) + (rand() % 100 / (float)100);
    }

    srand(time(NULL));

    // Then, we will swap the elements to make the elements in the array "randomized"
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

// Partition function that returns the index + 1 of the pivot
int partition(parcel *parcelArray, int head, int tail)
{
    int id_hold = parcelArray[tail].parcel_ID;
    int point = head - 1;

    // Comparison is done here to swap the elements smaller than the pivot to index point
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

    // pivot element is swapped with the index of (last smaller element) + 1
    parcel parcelHold = parcelArray[tail];
    parcelArray[tail] = parcelArray[point + 1];
    parcelArray[point + 1] = parcelHold;

    return point + 1;
}

// QuickSort Function that do the recursive calls
void quickSort(parcel *parcelArray, int head, int tail)
{
    if (head < tail)
    {
        // Getting the pivot
        int pivot = partition(parcelArray, head, tail);

        // Recursive calls here
        quickSort(parcelArray, head, pivot - 1);
        quickSort(parcelArray, pivot + 1, tail);
    }
}

int main()
{
    bool menu_status = true, show_unsort = false, show_sort = false;

    // Prompt user to input the number of parcels
    int n;
    cout << "Please enter the number of parcels.\n";
    cin >> n;

    // This is the menu that the user can choose either show/hide the unsorted/sorted parcel list
    while (menu_status)
    {
        int choice;

        if (!show_unsort)
        {
            if (!show_sort)
            {
                cout << "1. Show all the unsorted parcel\n";
                cout << "2. Show all the sorted parcel\n";
                cout << "3. Proceed\n";
                cout << "Your Choice = ";
                cin >> choice;
                cout << endl;

                switch (choice)
                {
                case 1:
                    show_unsort = true;
                    break;
                case 2:
                    show_sort = true;
                    break;
                case 3:
                    menu_status = false;
                    break;
                }
            }
            else
            {
                cout << "1. Show all the unsorted parcel\n";
                cout << "2. Hide all the sorted parcel\n";
                cout << "3. Proceed\n";
                cout << "Your Choice = ";
                cin >> choice;
                cout << endl;

                switch (choice)
                {
                case 1:
                    show_unsort = true;
                    break;
                case 2:
                    show_sort = false;
                    break;
                case 3:
                    menu_status = false;
                    break;
                }
            }
        }
        else
        {
            if (!show_sort)
            {
                cout << "1. Hide all the unsorted parcel\n";
                cout << "2. Show all the sorted parcel\n";
                cout << "3. Proceed\n";
                cout << "Your Choice = ";
                cin >> choice;
                cout << endl;

                switch (choice)
                {
                case 1:
                    show_unsort = false;
                    break;
                case 2:
                    show_sort = true;
                    break;
                case 3:
                    menu_status = false;
                    break;
                }
            }
            else
            {
                cout << "1. Hide all the unsorted parcel\n";
                cout << "2. Hide all the sorted parcel\n";
                cout << "3. Proceed\n";
                cout << "Your Choice = ";
                cin >> choice;
                cout << endl;

                switch (choice)
                {
                case 1:
                    show_unsort = false;
                    break;
                case 2:
                    show_sort = false;
                    break;
                case 3:
                    menu_status = false;
                    break;
                }
            }
        }
    }

    parcel *parcelArray = new parcel[n];
    parcel *parcelArrayCopy = new parcel[n];

    // The randomized parcel array is assigned to parcelArray
    parcelArray = randomParcel(n);

    // Another copy is made just in case the user wants to show the unsorted parcel list
    for (int i = 0; i < n; i++)
    {
        parcelArrayCopy[i] = parcelArray[i];
    }

    // Start and end time is assigned here to record the time taken for the sorting
    auto start = chrono::high_resolution_clock::now();
    quickSort(parcelArray, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    // Different time units are used here
    auto timeTaken_second = chrono::duration_cast<chrono::seconds>(end - start);
    auto timeTaken_millisecond = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto timeTaken_microsecond = chrono::duration_cast<chrono::microseconds>(end - start);
    auto timeTaken_nanosecond = chrono::duration_cast<chrono::nanoseconds>(end - start);

    cout << "Time taken to perform the sorting = " << timeTaken_second.count() << " seconds\n";
    cout << "\t\t\t\t  = " << timeTaken_millisecond.count() << " milliseconds\n";
    cout << "\t\t\t\t  = " << timeTaken_microsecond.count() << " microseconds\n";
    cout << "\t\t\t\t  = " << timeTaken_nanosecond.count() << " nanoseconds\n\n";

    // If the user chose to show the unsorted parcel list, this will run
    if (show_unsort)
    {
        cout << "----------------------\n";
        cout << "|Unsorted Parcel List|\n";
        cout << "----------------------\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Parcel ID = " << parcelArrayCopy[i].parcel_ID << endl;
            cout << "Parcel Cost = RM" << setprecision(2) << fixed << parcelArrayCopy[i].cost << endl;
        }
        cout << endl;
    }

    // If the user chose to show the sorted parcel list, this will run
    if (show_sort)
    {
        cout << "--------------------\n";
        cout << "|Sorted Parcel List|\n";
        cout << "--------------------\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Parcel ID = " << parcelArray[i].parcel_ID << endl;
            cout << "Parcel Cost RM= " << setprecision(2) << fixed << parcelArray[i].cost << endl;
        }
        cout << endl;
    }

    return 0;
}
#include <iostream>
using namespace std;

int *FoolSort(int *arr, int low, int high)
{
    if (high > low)
        if (arr[high] < arr[low])
        {
            int tmp = arr[high];
            arr[high] = arr[low];
            arr[low] = tmp;
        }
    if ((high - low) > 1)
    {
        int t = (high - low + 1) / 3;
        FoolSort(arr, low, high - t);
        FoolSort(arr, low + t, high);
        FoolSort(arr, low, high - t);
    }

    return arr;
}

int main()
{
    int n, *arr;
    cin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    FoolSort(arr, 0, n - 1);

    cout << "\n >> ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
}
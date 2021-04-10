#include <iostream>
using namespace std;

int TernarySearch(int n, int *arr, int key)
{
    int loc = 0, left = 0, right = n - 1, mid1, mid2;

    while (left <= right && !loc)
    {
        if (key == arr[mid1 = left + (right - left) / 3])
            loc = mid1;
        else if (key == arr[mid2 = left + (right - left) * 2 / 3])
            loc = mid2;
        else if (key < mid1)
            right = mid2 - 1;
        else if (key > mid2)
            left = mid1 + 1;
        else
        {
            right = mid2 - 1;
            left = mid1 + 1;
        }
    }

    return loc;
}

int main()
{
    int n, key, *arr;
    cin >> n >> key;
    arr = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "\n>> index: " << TernarySearch(n, arr, key) << '\n';
}
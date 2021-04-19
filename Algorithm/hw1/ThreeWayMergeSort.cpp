// https://www.random.org/integer-sets/?sets=1&num=30&min=1&max=99&seqnos=on&order=index&format=html&rnd=new

#include <iostream>
using namespace std;

int *arr, *tmp;

void Merge(int left, int right)
{
    int endI = (left * 2 + right) / 3;
    int endJ = (left + right * 2) / 3;

    // Compare 3 partition and store
    int i = left, j = endI + 1, k = endJ + 1, l = left;
    while (i <= endI && j <= endJ && k <= right)
    {
        if (arr[i] <= arr[j] && arr[i] <= arr[k])
            tmp[l++] = arr[i++];
        else if (arr[j] <= arr[i] && arr[j] <= arr[k])
            tmp[l++] = arr[j++];
        else
            tmp[l++] = arr[k++];
    }

    // Compare 2 partition and store
    if (i > endI)
    {
        i = k;
        endI = right;
    }
    else if (j > endJ)
    {
        j = k;
        endJ = right;
    }
    while (i <= endI && j <= endJ)
        tmp[l++] = arr[i] <= arr[j] ? arr[i++] : arr[j++];

    // Store last partition
    k = i > endI ? j : i;
    while (l <= right)
        tmp[l++] = arr[k++];

    // Copy tmp to arr
    // for (i = left; i <= right; i++)
    //     arr[i] = tmp[i];
    copy(tmp + left, tmp + right + 1, arr + left);
}
void ThreeWayMergeSort(int left, int right)
{
    if (left >= right)
        return;

    int mid1 = (left * 2 + right) / 3;
    int mid2 = (left + right * 2) / 3;

    ThreeWayMergeSort(left, mid1);
    ThreeWayMergeSort(mid1 + 1, mid2);
    ThreeWayMergeSort(mid2 + 1, right);
    Merge(left, right);
}

int main()
{
    int n;
    cin >> n;
    arr = new int[n];
    tmp = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    ThreeWayMergeSort(0, n - 1);

    cout << "\n>> ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
}
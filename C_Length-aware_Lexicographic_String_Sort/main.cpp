#include <iostream>
#include <vector>
#include <string>
using namespace std;

void insertion_sort(vector<string> &v, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        string key = v[i];
        int j = i - 1;
        while (j >= low && (v[j].length() > key.length() || (v[j].length() == key.length() && v[j] > key)))
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

void mergeSort(vector<string> &a, vector<string> &tmp, int left, int right)
{
    if (left >= right)
        return;

    if (right - left < 15)
    {
        insertion_sort(a, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(a, tmp, left, mid);
    mergeSort(a, tmp, mid + 1, right);

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (a[i].size() < a[j].size() ||
            (a[i].size() == a[j].size() && a[i] <= a[j]))
        {
            tmp[k++] = a[i++];
        }
        else
        {
            tmp[k++] = a[j++];
        }
    }

    while (i <= mid)
    {
        tmp[k++] = a[i++];
    }

    while (j <= right)
    {
        tmp[k++] = a[j++];
    }

    for (int h = left; h <= right; h++)
    {
        a[h] = tmp[h];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    vector<string> tmp(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    mergeSort(a, tmp, 0, n - 1);

    cout << n << '\n';

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << '\n';
    }

    return 0;
}

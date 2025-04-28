#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge two sorted halves
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];

    for (int i = 0; i < temp.size(); ++i)
        arr[l + i] = temp[i];
}

// Parallel Merge Sort
void parallel_merge_sort(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallel_merge_sort(arr, l, m);
        #pragma omp section
        parallel_merge_sort(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int& x : arr) cin >> x;

    omp_set_num_threads(4);
    parallel_merge_sort(arr, 0, n - 1);

    cout << "Sorted array:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}

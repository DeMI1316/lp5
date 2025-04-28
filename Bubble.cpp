#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Parallel Bubble Sort
void parallel_bubble_sort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int& x : arr) cin >> x;

    omp_set_num_threads(4);
    parallel_bubble_sort(arr, n);

    cout << "Sorted array:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}

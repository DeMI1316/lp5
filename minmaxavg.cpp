#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;  

int reduce(const vector<int>& arr, auto op) {
    vector<int> temp = arr;
    while (temp.size() > 1) {
        vector<int> next;
        for (size_t i = 0; i + 1 < temp.size(); i += 2)
            next.push_back(op(temp[i], temp[i+1]));
        if (temp.size() % 2) next.push_back(temp.back());
        temp = next;
    }
    return temp[0];
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> data(n);
    cout << "Enter elements: ";
    for (int& x : data) cin >> x;

    int sum = reduce(data, [](int a, int b) { return a + b; });
    int mn = reduce(data, [](int a, int b) { return min(a, b); });
    int mx = reduce(data, [](int a, int b) { return max(a, b); });

    cout << "Sum: " << sum << "\n";
    cout << "Min: " << mn << "\n";
    cout << "Max: " << mx << "\n";
    cout << "Average: " << static_cast<double>(sum) / n << "\n";

    return 0;
}

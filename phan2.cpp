#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    vector<int> w = {2, 3, 4, 5, 7};
    vector<int> v = {3, 7, 9, 12, 16};
    vector<char> items = {'A', 'B', 'C', 'D', 'E'};
    int W = 11, n = 5;

    vector<vector<int>> f(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j >= w[i-1]) {
                f[i][j] = max(f[i-1][j], f[i-1][j - w[i-1]] + v[i-1]);
            } else {
                f[i][j] = f[i-1][j];
            }
        }
    }

    cout << "Bang f quy hoach dong:\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            cout << setw(4) << f[i][j];
        }
        cout << "\n";
    }

    cout << "\nGia tri lon nhat: " << f[n][W] << "\n";

    int curr_w = W;
    vector<char> chosen_items;
    for (int i = n; i > 0; i--) {
        if (f[i][curr_w] != f[i-1][curr_w]) {
            chosen_items.push_back(items[i-1]);
            curr_w -= w[i-1];
        }
    }

    cout << "Tap do vat duoc chon: ";
    for (int i = chosen_items.size() - 1; i >= 0; i--) {
        cout << chosen_items[i] << " ";
    }
    cout << "\n";

    return 0;
}
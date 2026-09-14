#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int idx, vector<int> coins, int target) {
    int rem = target;
    vector<int> greedy_res;
    vector<int> sorted_coins = coins;
    sort(sorted_coins.rbegin(), sorted_coins.rend());
    
    for (int c : sorted_coins) {
        while (rem >= c) {
            greedy_res.push_back(c);
            rem -= c;
        }
    }
    
    vector<int> f(target + 1, 1e9);
    vector<int> parent(target + 1, -1);
    f[0] = 0;
    
    for (int i = 1; i <= target; i++) {
        for (int c : coins) {
            if (i >= c && f[i - c] + 1 < f[i]) {
                f[i] = f[i - c] + 1;
                parent[i] = c;
            }
        }
    }
    
    vector<int> dp_res;
    int curr = target;
    while (curr > 0 && f[curr] != 1e9) {
        dp_res.push_back(parent[curr]);
        curr -= parent[curr];
    }
    sort(dp_res.rbegin(), dp_res.rend());
    
    cout << "Bo " << idx << ":" << endl;
    cout << "  Greedy: " << greedy_res.size() << " to (";
    for (size_t i = 0; i < greedy_res.size(); i++) {
        cout << greedy_res[i] << (i == greedy_res.size() - 1 ? "" : "+");
    }
    cout << ")" << endl;
    
    cout << "  DP: " << dp_res.size() << " to (";
    for (size_t i = 0; i < dp_res.size(); i++) {
        cout << dp_res[i] << (i == dp_res.size() - 1 ? "" : "+");
    }
    cout << ")" << endl;
}

int main() {
    solve(1, {1, 6, 9}, 12);
    solve(2, {1, 5, 10, 20, 50}, 85);
    solve(3, {1, 7, 12}, 20);
    solve(4, {1, 2, 5, 10, 20, 50, 100}, 38);
    solve(5, {1, 6, 10}, 12);
    solve(6, {1, 4, 15, 20}, 23);
    return 0;
}
 

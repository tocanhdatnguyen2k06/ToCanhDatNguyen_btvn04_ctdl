#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Activity {
    string name;
    int start;
    int end;
    int length() const { return end - start; }
};

int main() {
    vector<Activity> acts = {
        {"H1", 1, 5}, {"H2", 2, 5}, {"H3", 2, 6}, {"H4", 3, 4}, {"H5", 4, 8},
        {"H6", 6, 9}, {"H7", 8, 11}, {"H8", 9, 14}, {"H9", 11, 13}, {"H10", 12, 15}
    };

    // 1. Kết thúc sớm nhất
    vector<Activity> acts1 = acts;
    sort(acts1.begin(), acts1.end(), [](const Activity& a, const Activity& b) {
        return a.end != b.end ? a.end < b.end : a.start < b.start;
    });
    vector<string> r1;
    int last_end = -1;
    for (const auto& a : acts1) {
        if (a.start >= last_end) { r1.push_back(a.name); last_end = a.end; }
    }

    // 2. Bắt đầu sớm nhất
    vector<Activity> acts2 = acts;
    sort(acts2.begin(), acts2.end(), [](const Activity& a, const Activity& b) {
        return a.start != b.start ? a.start < b.start : a.end < b.end;
    });
    vector<string> r2;
    last_end = -1;
    for (const auto& a : acts2) {
        if (a.start >= last_end) { r2.push_back(a.name); last_end = a.end; }
    }

    // 3. Ngắn nhất
    vector<Activity> acts3 = acts;
    sort(acts3.begin(), acts3.end(), [](const Activity& a, const Activity& b) {
        return a.length() != b.length() ? a.length() < b.length() : a.end < b.end;
    });
    vector<Activity> rem3 = acts3;
    vector<string> r3;
    while (!rem3.empty()) {
        Activity best = rem3[0];
        r3.push_back(best.name);
        vector<Activity> next_rem;
        for (const auto& a : rem3) {
            if (a.start >= best.end || a.end <= best.start) next_rem.push_back(a);
        }
        rem3 = next_rem;
    }

    // 4. Ít chồng lấn nhất
    vector<Activity> rem4 = acts;
    vector<string> r4;
    while (!rem4.empty()) {
        int min_conf = 1e9, best_idx = 0;
        for (size_t i = 0; i < rem4.size(); ++i) {
            int count = 0;
            for (size_t j = 0; j < rem4.size(); ++j) {
                if (!(rem4[j].end <= rem4[i].start || rem4[j].start >= rem4[i].end)) count++;
            }
            if (count < min_conf || (count == min_conf && rem4[i].length() < rem4[best_idx].length())) {
                min_conf = count;
                best_idx = i;
            }
        }
        Activity best = rem4[best_idx];
        r4.push_back(best.name);
        vector<Activity> next_rem;
        for (const auto& a : rem4) {
            if (a.start >= best.end || a.end <= best.start) next_rem.push_back(a);
        }
        rem4 = next_rem;
    }

    cout << "1. Ket thuc som nhat: ";
    for (size_t i = 0; i < r1.size(); ++i) cout << r1[i] << (i == r1.size() - 1 ? "" : ", ");
    cout << "\n2. Bat dau som nhat: ";
    for (size_t i = 0; i < r2.size(); ++i) cout << r2[i] << (i == r2.size() - 1 ? "" : ", ");
    cout << "\n3. Ngan nhat: ";
    for (size_t i = 0; i < r3.size(); ++i) cout << r3[i] << (i == r3.size() - 1 ? "" : ", ");
    cout << "\n4. It chong lan nhat: ";
    for (size_t i = 0; i < r4.size(); ++i) cout << r4[i] << (i == r4.size() - 1 ? "" : ", ");
    cout << endl;

    return 0;
}
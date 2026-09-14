#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

int main() {
    vector<string> words;
    words.push_back("em"); 
    words.push_back("hoc"); 
    words.push_back("bai"); 
    words.push_back("toan");

    map<string, double> emit_em;
    emit_em["N"] = 0.30; emit_em["V"] = 0.05;
    map<string, double> emit_hoc;
    emit_hoc["N"] = 0.10; emit_hoc["V"] = 0.25;
    map<string, double> emit_bai;
    emit_bai["N"] = 0.20; emit_bai["V"] = 0.03;
    map<string, double> emit_toan;
    emit_toan["N"] = 0.15; emit_toan["V"] = 0.04;

    map<string, double> trans_start;
    trans_start["N"] = 0.70; trans_start["V"] = 0.40;
    map<string, double> trans_N;
    trans_N["N"] = 0.25; trans_N["V"] = 0.35;
    map<string, double> trans_V;
    trans_V["N"] = 0.28; trans_V["V"] = 0.15;

    vector<map<string, double> > f(4);
    vector<map<string, string> > parent(4);

    f[0]["N"] = trans_start["N"] * emit_em["N"];
    f[0]["V"] = trans_start["V"] * emit_em["V"];
    parent[0]["N"] = "None";
    parent[0]["V"] = "None";

    for (int i = 1; i < 4; ++i) {
        map<string, double> curr_emit;
        if (i == 1) curr_emit = emit_hoc;
        else if (i == 2) curr_emit = emit_bai;
        else curr_emit = emit_toan;

        string tags[2] = {"N", "V"};
        for (int t = 0; t < 2; ++t) {
            string tag = tags[t];
            string best_p = "";
            double best_val = -1.0;

            for (int pt = 0; pt < 2; ++pt) {
                string ptag = tags[pt];
                double t_prob = (ptag == "N") ? trans_N[tag] : trans_V[tag];
                double val = f[i-1][ptag] * t_prob * curr_emit[tag];
                if (val > best_val) {
                    best_val = val;
                    best_p = ptag;
                }
            }
            f[i][tag] = best_val;
            parent[i][tag] = best_p;
        }
    }

    cout << fixed << setprecision(6);
    for (int i = 0; i < 4; ++i) {
        cout << "i=" << (i+1) << " | " << words[i] 
             << " | f[N]=" << f[i]["N"] << " | f[V]=" << f[i]["V"] 
             << " | Truoc_N=" << parent[i]["N"] << " | Truoc_V=" << parent[i]["V"] << endl;
    }

    string curr = (f[3]["N"] > f[3]["V"]) ? "N" : "V";
    vector<string> res;
    res.push_back(curr);
    for (int i = 3; i > 0; --i) {
        curr = parent[i][curr];
        res.push_back(curr);
    }
    cout << "Nhan toi uu: ";
    for (int i = 3; i >= 0; --i) {
        cout << res[i] << (i == 0 ? "" : " ");
    }
    cout << endl;

    return 0;
}


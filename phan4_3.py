def viterbi_decoding():
    words = ["em", "học", "bài", "toán"]
    tags = ["N", "V"]
    emit = {
        "em": {"N": 0.30, "V": 0.05},
        "học": {"N": 0.10, "V": 0.25},
        "bài": {"N": 0.20, "V": 0.03},
        "toán": {"N": 0.15, "V": 0.04}
    }
    trans = {
        "start": {"N": 0.70, "V": 0.40},
        "N": {"N": 0.25, "V": 0.35},
        "V": {"N": 0.28, "V": 0.15}
    }
    f = [{} for _ in range(4)]
    parent = [{} for _ in range(4)]
    for t in tags:
        f[0][t] = trans["start"][t] * emit["em"][t]
        parent[0][t] = "None"
    for i in range(1, 4):
        w = words[i]
        for t in tags:
            best_p, best_val = None, -1.0
            for pt in tags:
                val = f[i-1][pt] * trans[pt][t] * emit[w][t]
                if val > best_val:
                    best_val = val
                    best_p = pt
            f[i][t] = best_val
            parent[i][t] = best_p
    for i, w in enumerate(words):
        p_n = str(parent[i]["N"])
        p_v = str(parent[i]["V"])
        print(f"i={i+1} | {w:<4} | f[N]={f[i]['N']:.6f} | f[V]={f[i]['V']:.6f} | Truoc_N={p_n:<4} | Truoc_V={p_v}")
    curr = "N" if f[3]["N"] > f[3]["V"] else "V"
    res = [curr]
    for i in range(3, 0, -1):
        curr = parent[i][curr]
        res.append(curr)
    print("\nNhan toi uu:", " ".join(reversed(res)))

viterbi_decoding()

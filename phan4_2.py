class Activity:
    def __init__(self, name, start, end):
        self.name = name
        self.start = start
        self.end = end
        self.length = end - start

def solve():
    data = [
        ("H1", 1, 5), ("H2", 2, 5), ("H3", 2, 6), ("H4", 3, 4), ("H5", 4, 8),
        ("H6", 6, 9), ("H7", 8, 11), ("H8", 9, 14), ("H9", 11, 13), ("H10", 12, 15)
    ]
    acts = [Activity(n, s, f) for n, s, f in data]

    # 1. Kết thúc sớm nhất
    acts_fin = sorted(acts, key=lambda x: (x.end, x.start))
    r1, last_end = [], -1
    for a in acts_fin:
        if a.start >= last_end:
            r1.append(a.name)
            last_end = a.end

    # 2. Bắt đầu sớm nhất
    acts_start = sorted(acts, key=lambda x: (x.start, x.end))
    r2, last_end = [], -1
    for a in acts_start:
        if a.start >= last_end:
            r2.append(a.name)
            last_end = a.end

    # 3. Ngắn nhất
    acts_len = sorted(acts, key=lambda x: (x.length, x.end))
    rem3, r3 = acts_len.copy(), []
    while rem3:
        best = rem3.pop(0)
        r3.append(best.name)
        rem3 = [a for a in rem3 if a.start >= best.end or a.end <= best.start]

    # 4. Ít chồng lấn nhất
    rem4, r4 = acts.copy(), []
    while rem4:
        best_idx, min_conf = 0, 1000
        for i, a in enumerate(rem4):
            count = sum(1 for b in rem4 if not (b.end <= a.start or b.start >= a.end))
            if count < min_conf or (count == min_conf and a.length < rem4[best_idx].length):
                min_conf, best_idx = count, i
        best = rem4[best_idx]
        r4.append(best.name)
        rem4 = [a for a in rem4 if a.start >= best.end or a.end <= best.start]

    print("1. Ket thuc som nhat:", ", ".join(r1))
    print("2. Bat dau som nhat:", ", ".join(r2))
    print("3. Ngan nhat:", ", ".join(r3))
    print("4. It chong lan nhat:", ", ".join(r4))

solve()
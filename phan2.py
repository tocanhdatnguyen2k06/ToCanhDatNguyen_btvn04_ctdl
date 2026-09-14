
def knapsack_01():
    w = [2, 3, 4, 5, 7]
    v = [3, 7, 9, 12, 16]
    items = ['A', 'B', 'C', 'D', 'E']
    W, n = 11, 5

    f = [[0] * (W + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(W + 1):
            if j >= w[i-1]:
                f[i][j] = max(f[i-1][j], f[i-1][j - w[i-1]] + v[i-1])
            else:
                f[i][j] = f[i-1][j]

    print("Bang f quy hoach dong:")
    for row in f:
        print(" ".join(f"{x:3d}" for x in row))

    print(f"Gia tri lon nhat: {f[n][W]}")

    curr_w = W
    chosen_items = []
    for i in range(n, 0, -1):
        if f[i][curr_w] != f[i-1][curr_w]:
            chosen_items.append(items[i-1])
            curr_w -= w[i-1]

    print(f"Tap do vat duoc chon: {chosen_items[::-1]}")

if __name__ == "__main__":
    knapsack_01()
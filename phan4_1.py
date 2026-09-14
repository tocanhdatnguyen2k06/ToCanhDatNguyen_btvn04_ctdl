def solve_coin_change():
    systems = [
        ([1, 6, 9], 12),
        ([1, 5, 10, 20, 50], 85),
        ([1, 7, 12], 20),
        ([1, 2, 5, 10, 20, 50, 100], 38),
        ([1, 6, 10], 12),
        ([1, 4, 15, 20], 23)
    ]
    
    for idx, (coins, target) in enumerate(systems, 1):
        rem = target
        greedy_res = []
        for c in sorted(coins, reverse=True):
            while rem >= c:
                greedy_res.append(c)
                rem -= c
        
        f = [float('inf')] * (target + 1)
        f[0] = 0
        parent = [-1] * (target + 1)
        
        for i in range(1, target + 1):
            for c in coins:
                if i >= c and f[i - c] + 1 < f[i]:
                    f[i] = f[i - c] + 1
                    parent[i] = c
                    
        dp_res = []
        curr = target
        while curr > 0 and f[curr] != float('inf'):
            dp_res.append(parent[curr])
            curr -= parent[curr]
            
        print(f"Bo {idx}:")
        print(f"  Greedy: {len(greedy_res)} to ({'+'.join(map(str, greedy_res))})")
        print(f"  DP: {len(dp_res)} to ({'+'.join(map(str, sorted(dp_res, reverse=True)))})")

solve_coin_change()

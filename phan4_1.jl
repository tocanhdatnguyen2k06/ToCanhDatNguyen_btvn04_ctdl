function solve_coin_change()
    systems = [
        ([1, 6, 9], 12),
        ([1, 5, 10, 20, 50], 85),
        ([1, 7, 12], 20),
        ([1, 2, 5, 10, 20, 50, 100], 38),
        ([1, 6, 10], 12),
        ([1, 4, 15, 20], 23)
    ]
    
    for (idx, (coins, target)) in enumerate(systems)
        rem = target
        greedy_res = Int[]
        for c in sort(coins, rev=true)
            while rem >= c
                push!(greedy_res, c)
                rem -= c
            end
        end
        
        f = fill(typemax(Int) - 1, target + 1)
        f[1] = 0
        parent = fill(-1, target + 1)
        
        for i in 1:target
            for c in coins
                if i >= c && f[i - c + 1] + 1 < f[i + 1]
                    f[i + 1] = f[i - c + 1] + 1
                    parent[i + 1] = c
                end
            end
        end
        
        dp_res = Int[]
        curr = target
        while curr > 0 && f[curr + 1] != typemax(Int) - 1
            push!(dp_res, parent[curr + 1])
            curr -= parent[curr + 1]
        end
        sort!(dp_res, rev=true)
        
        println("Bo $idx:")
        println("  Greedy: ", length(greedy_res), " to (", join(greedy_res, "+"), ")")
        println("  DP: ", length(dp_res), " to (", join(dp_res, "+"), ")")
    end
end

solve_coin_change()
 
 
 
 

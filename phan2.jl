function knapsack_01()
    w = [2, 3, 4, 5, 7]
    v = [3, 7, 9, 12, 16]
    items = ['A', 'B', 'C', 'D', 'E']
    W, n = 11, 5
    
    f = zeros(Int, n + 1, W + 1)
    
    for i in 1:n
        for j in 0:W
            if j >= w[i]
               f[i+1, j+1] = max(f[i, j+1], f[i, j - w[i] + 1] + v[i])
            else
               f[i+1, j+1] = f[i, j+1]
            end
        end
    end
    
    println("Bang f quy hoach dong:")
    for i in 1:(n+1)
        println(join([lpad(f[i, j], 4) for j in 1:(W+1)], ""))
    end
    
    println("\nGia tri lon nhat: ", f[n+1, W+1])
    
    curr_w = W
    chosen_items = Char[]
    for i in n:-1:1
        if f[i+1, curr_w+1] != f[i, curr_w+1]
            push!(chosen_items, items[i])
            curr_w -= w[i]
        end
    end
    
    println("Tap do vat duoc chon: ", reverse(chosen_items))
end

knapsack_01()
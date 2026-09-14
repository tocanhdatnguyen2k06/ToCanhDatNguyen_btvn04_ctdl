using Printf

function viterbi_decoding()
    words = ["em", "học", "bài", "toán"]
    tags = ["N", "V"]
    emit = Dict(
        "em" => Dict("N" => 0.30, "V" => 0.05),
        "học" => Dict("N" => 0.10, "V" => 0.25),
        "bài" => Dict("N" => 0.20, "V" => 0.03),
        "toán" => Dict("N" => 0.15, "V" => 0.04)
    )
    trans = Dict(
        "start" => Dict("N" => 0.70, "V" => 0.40),
        "N" => Dict("N" => 0.25, "V" => 0.35),
        "V" => Dict("N" => 0.28, "V" => 0.15)
    )
    f = [Dict{String, Float64}() for _ in 1:4]
    parent = [Dict{String, String}() for _ in 1:4]
    for t in tags
        f[1][t] = trans["start"][t] * emit["em"][t]
        parent[1][t] = "None"
    end
    for i in 2:4
        w = words[i]
        for t in tags
            best_p, best_val = "", -1.0
            for pt in tags
                val = f[i-1][pt] * trans[pt][t] * emit[w][t]
                if val > best_val
                    best_val = val
                    best_p = pt
                end
            end
            f[i][t] = best_val
            parent[i][t] = best_p
        end
    end
    for i in 1:4
        @printf("i=%d | %-4s | f[N]=%.6f | f[V]=%.6f | Truoc_N=%-4s | Truoc_V=%s\n", 
            i, words[i], f[i]["N"], f[i]["V"], parent[i]["N"], parent[i]["V"])
    end
    curr = f[4]["N"] > f[4]["V"] ? "N" : "V"
    res = [curr]
    for i in 4:-1:2
        curr = parent[i][curr]
        push!(res, curr)
    end
    println("\nNhan toi uu: ", join(reverse(res), " "))
end

viterbi_decoding()


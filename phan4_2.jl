struct Activity
    name::String
    start::Int
    end_time::Int
    length::Int
    Activity(name, s, e) = new(name, s, e, e - s)
end

function solve()
    acts = [
        Activity("H1", 1, 5), Activity("H2", 2, 5), Activity("H3", 2, 6),
        Activity("H4", 3, 4), Activity("H5", 4, 8), Activity("H6", 6, 9),
        Activity("H7", 8, 11), Activity("H8", 9, 14), Activity("H9", 11, 13),
        Activity("H10", 12, 15)
    ]

    # 1. Kết thúc sớm nhất
    acts1 = sort(acts, by = x -> (x.end_time, x.start))
    r1, last_end = String[], -1
    for a in acts1
        if a.start >= last_end
            push!(r1, a.name)
            last_end = a.end_time
        end
    end

    # 2. Bắt đầu sớm nhất
    acts2 = sort(acts, by = x -> (x.start, x.end_time))
    r2, last_end = String[], -1
    for a in acts2
        if a.start >= last_end
            push!(r2, a.name)
            last_end = a.end_time
        end
    end

    # 3. Ngắn nhất
    acts3 = sort(acts, by = x -> (x.length, x.end_time))
    rem3, r3 = copy(acts3), String[]
    while !isempty(rem3)
        best = popfirst!(rem3)
        push!(r3, best.name)
        filter!(a -> a.start >= best.end_time || a.end_time <= best.start, rem3)
    end

    # 4. Ít chồng lấn nhất (Đổi tên biến count thành cnt)
    rem4, r4 = copy(acts), String[]
    while !isempty(rem4)
        best_idx, min_conf = 1, 1000
        for i in 1:length(rem4)
            cnt = count(b -> !(b.end_time <= rem4[i].start || b.start >= rem4[i].end_time), rem4)
            if cnt < min_conf || (cnt == min_conf && rem4[i].length < rem4[best_idx].length)
                min_conf, best_idx = cnt, i
            end
        end
        best = rem4[best_idx]
        push!(r4, best.name)
        filter!(a -> a.start >= best.end_time || a.end_time <= best.start, rem4)
    end

    println("1. Ket thuc som nhat: ", join(r1, ", "))
    println("2. Bat dau som nhat: ", join(r2, ", "))
    println("3. Ngan nhat: ", join(r3, ", "))
    println("4. It chong lan nhat: ", join(r4, ", "))
end

solve()
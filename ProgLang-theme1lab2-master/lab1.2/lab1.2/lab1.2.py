def inputArr():
    return  list(map(int, input().split()))


def output(n, i, ans, pr, d):
    if(n != 0):
        if(i == 0):
            price = sorted(inputArr())
            dist = sorted(inputArr())

            return output(n - 1, i + 1, '\n' + str(price [i]) + '-' + str(dist[n - 1]) , price, dist)

        else:
    
            return output(n - 1, i + 1, str(ans) + '\n' + str(pr[i]) + '-' + str(d[n - 1]), pr, d)

    else:
       return str(ans)

print(output(int(input()), 0, 0, 0, 0), sep="\n")

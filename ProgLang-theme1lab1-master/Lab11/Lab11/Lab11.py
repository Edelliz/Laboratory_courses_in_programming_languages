def isOdd(x, count, ans):   
    a = x//10

    if a >= 0:
        if x % 2 == 1:          
            if a == 0:
                return ans + ((x % 10) * pow(10, count + 1 ))

            else:
                return isOdd(a, count + 1, ans + ((x % 10) * pow(10, count + 1 )))

        else: 
            if a == 0:
                return ans

            else: 
                return isOdd(a, count, ans)

print(isOdd(int(input()), -1, 0))




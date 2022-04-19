def culcVector(arr, coef):
	vec1x = (arr[2] - arr[0]) * coef
	vec2x = (arr[4] - arr[2]) * coef
	vec3x = (arr[0] - arr[4]) * coef
				   
	vec1y = (arr[3] - arr[1]) * coef
	vec2y = (arr[5] - arr[3]) * coef
	vec3y = (arr[1] - arr[5]) * coef

	return [vec1x, vec1y, vec2x, vec2y, vec3x, vec3y]

def inPUT(arr, coef):
	return list(map(lambda x: culcVector(x, coef), arr))

def inputArr(n):
	if(n > 1):
		return[list(map(int, input().split()))] + inputArr(n - 1)
	else:
		return [list(map(int, input().split()))]

print(*inPUT(inputArr(int(input())), int(input())), sep="\n")





		






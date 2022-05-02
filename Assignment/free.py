def binary_search(target, data):
    left = 0
    right = len(data) - 1

    while(left <= right) :
        mid = (left + right) // 2
        if(data[mid][0] == target):
            return mid 
        elif(data[mid][0] < target):
            left = mid + 1
        else:
            right = mid -1
    if(right == -1) :
        return None
    else :
        return right #못찾으면 target값 기준으로 더 작은데이터쪽 index출력

rf = open('free.inp','r')
N = int(rf.readline())

requests = []
DP_v = [0] * N
DP_d = [0] * N

for x in range(N) :
    line = list(map(int,rf.readline().split()))
    temp = line[0]
    line[0] = line[1]
    line[1] = temp
    requests.append(line)

rf.close()
requests.sort() #0이 끝 1이 시작 2가 가치, 끝을 기준으로 정렬

DP_v[0] = requests[0][2]
DP_d[0] = requests[0][0] - requests[0][1] + 1

for x in range(1,N) :
    A = DP_v[x-1]
    flag = 0
    for y in range(x) :
        if(requests[x][1] > requests[y][0]) :
            continue
        else :
            B = y-1
            flag = 1
            break
    if(flag == 0) :
        B = x-1
    #B = binary_search(requests[x][1]-1,requests) 버그나서 사용보류
    if(B == -1) :
        C = 0 + requests[x][2]
    else :
        C = DP_v[B] + requests[x][2] - 10
    if(A > C) :
        DP_v[x] = A
        DP_d[x] = DP_d[x-1]
    elif(A == C) :
        DP_v[x] = A
        if(B == -1) :
            DP_d[x] = min(DP_d[x-1],requests[x][0] - requests[x][1] + 1)
        else :
            DP_d[x] = min(DP_d[x-1],DP_d[B] + requests[x][0] - requests[x][1] + 1)
    else :
        DP_v[x] = C
        if(B == -1) :
            DP_d[x] = requests[x][0] - requests[x][1] + 1
        else :
            DP_d[x] = DP_d[B] + requests[x][0] - requests[x][1] + 1

f = open('free.out','w')

the_max = max(DP_v)
the_min = 1095

for x in range(N) :
    if(DP_v[x] == the_max and DP_d[x] < the_min) :
        the_min = DP_d[x]

f.write(str(the_max)+' '+str(the_min))
    
f.close()

    
